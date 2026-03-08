#include "parser.hpp"
#include "../state/state.hpp"

#include <algorithm>
#include <assert.h>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::map<std::string, std::string> token_regexp;

State *parse_regex(std::string &file_name)
{
	std::fstream reg_file(file_name, std::ios_base::in);
	auto list = parse_file(reg_file);
	Fragment *f = new Fragment();

	if (list.size() == 1)
	{
		f = list.back();
		return f->state;
	}

	while (list.size() > 1)
	{
		alternation(list, f);
	}

	reg_file.close();

	f = list.back();

	return f->state;
}

std::vector<Fragment *> parse_file(std::fstream &file)
{
	std::string line;
	std::vector<Fragment *> result;
	int line_count = 0;

	while (std::getline(file, line))
	{
		line_count++;

		if (line.empty())
			continue;

		auto colon = line.find(':');

		if (line[colon - 1] != ' ' || line[colon + 1] != ' ')
		{
			std::cout << "Sytax error in line " << line_count
					  << ", probably spaces between token name, separator and expression missing!\n";
			return result;
		}

		std::string token_name = line.substr(0, colon - 1);
		std::string regexp = line.substr(colon + 2);
		regexp = pre_processing(regexp);

		// std::cout << regexp << "\n";
		token_regexp[token_name] = regexp;

		if (token_name[0] == '_')
		{
			continue;
		}

		regexp = convert_to_postfix_notation(regexp);
		// std::cout << regexp << "\n";

		auto frag = build_nfa(regexp);
		frag->final->token = token_name;

		result.push_back(frag);
	}

	return result;
}

std::string pre_processing(std::string &exp)
{
	std::string output;

	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '\"')
		{
			output += '\"';

			for (int j = i + 1; j < exp.size(); j++)
			{
				if (exp[j] == '\"')
				{
					i = j + 1;
					break;
				}
				output += exp[j];
			}
			output += '\"';
		}

		// [A-Z] or [a-z] or [0-9]
		if (exp[i] == '[')
		{
			if (exp[i + 1] == ']')
			{
				char begin = (char)33;
				char end = (char)127;
				output += "(";

				for (char k = begin; k < end; k++)
				{
					if (k == '\\')
					{
						continue;
					}
					// std::cout << k << std::endl;
					output += '\"';
					output += k;
					output += '\"';
					output += '|';
				}

				output.pop_back();
				output += ")";
				i += 2;
			}
			else if (exp[i + 1] == '<')
			{
				std::string tok_name;

				for (int j = i + 2; j < exp.size(); j++)
				{
					if (exp[j] == '>')
						break;
					tok_name += exp[j];
				}
				output += '(';

				if (token_regexp.find(tok_name) != token_regexp.end())
					output += token_regexp[tok_name];

				output += ')';

				i += 4 + tok_name.size();

				assert(exp[i] != ']');
				// [<TOKEN>]
			}
			else if (exp[i + 1] == '~')
			{
				std::vector<char> exclude;
				int j = i + 2;

				for (j = i + 2; j < exp.size(); j++)
				{
					if (exp[j] == ']')
						break;

					if (exp[j] == ',')
						continue;

					exclude.push_back(exp[j]);
				}

				char begin = (char)33;
				char end = (char)127;
				output += "(";

				for (char k = begin; k < end; k++)
				{
					if (std::find(exclude.begin(), exclude.end(), k) != exclude.end() || k == '\\')
					{
						continue;
					}
					// std::cout << k << std::endl;
					output += '\"';
					output += k;
					output += '\"';
					output += '|';
				}

				output.pop_back();
				output += ")";
				i = j + 1;
			}
			else
			{
				output += "(";

				char begin = exp[i + 1];
				char end = exp[i + 3];
				for (char k = begin; k <= end; k++)
				{
					output += '\"';
					output += k;
					output += '\"';
					output += '|';
				}

				output.pop_back();
				output += ")";
				i += 5;
			}
		}

		output += exp[i];
	}

	return output;
}

std::string convert_to_postfix_notation(std::string &exp)
{

	char operators_can_concat[] = {')', '[', '?', '*', '+'};
	char operators_in_exp[] = {
		'(', ')', '*', '|', '"', '.', '?', '+', '\\',
	};

	std::string postfix;

	// Convert to expression with concatenations
	// bad code inside this for loop
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '\"')
		{

			if (i > 0 && std::find(std::begin(operators_can_concat), std::end(operators_can_concat), exp[i - 1]) !=
							 std::end(operators_can_concat) ||
				std::isalpha(postfix.back()))
			{
				postfix += '.';
			}

			for (int j = i + 1; j < exp.size(); j++)
			{
				if (exp[j] == '\"')
				{
					i = i + (j - i) + 1;
					break;
				}

				if (j >= i + 2)
				{
					postfix += '.';
				}

				if (std::find(std::begin(operators_in_exp), std::end(operators_in_exp), exp[j]) !=
					std::end(operators_in_exp))
				{
					postfix += '\\';
					postfix += exp[j];
					continue;
				}

				postfix += exp[j];
			}
		}

		if (exp[i] == ' ')
			continue;

		if (exp[i] == '(' && std::isalpha(postfix.back()))
		{
			postfix += '.';
		}

		postfix += exp[i];
	}

	// Precedence
	// ()
	// * + ?
	// .
	// |

	// Shunting  yard algorithm below
	std::string output;

	char operators[] = {'*', '+', '?', '.', '|'};

	std::vector<char> op_stack;

	for (int i = 0; i < postfix.size(); i++)
	{
		if (std::find(std::begin(operators), std::end(operators), postfix[i]) != std::end(operators))
		{
			if (!op_stack.empty() && op_stack.back() == '(')
			{
				op_stack.push_back(postfix[i]);
			}
			else
			{

				while (!op_stack.empty() && op_stack.back() != '(')
				{
					int proc_stack, proc_postfix;

					for (int j = 0; j < std::size(operators); j++)
					{
						if (operators[j] == op_stack.back())
						{
							proc_stack = j;
						}

						if (operators[j] == postfix[i])
						{
							proc_postfix = j;
						}
					}

					if (proc_stack <= proc_postfix)
					{
						output += op_stack.back();
						op_stack.pop_back();
					}
					else
					{
						break;
					}
				}

				op_stack.push_back(postfix[i]);
			}
			continue;
		}

		if (postfix[i] == '\\')
		{
			output += "\\";
			output += postfix[i + 1];
			i += 1;
			continue;
		}

		if (postfix[i] == '(')
		{
			op_stack.push_back(postfix[i]);
			continue;
		}

		if (postfix[i] == ')')
		{
			while (op_stack.back() != '(')
			{
				output += op_stack.back();
				op_stack.pop_back();
			}
			op_stack.pop_back();
			continue;
		}

		output += postfix[i];
	}

	while (!op_stack.empty())
	{
		output += op_stack.back();
		op_stack.pop_back();
	}

	return output;
}
