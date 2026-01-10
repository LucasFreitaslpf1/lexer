#include "parser.hpp"
#include "../state/state.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

void parse_regex(std::string &file_name)
{
	std::vector<Fragment *> fragments;
	std::fstream reg_file(file_name, std::ios_base::in);
	std::string s = get_file_text(reg_file);

	std::string regexp = convert_to_postfix_notation(s);

	State *start = build_nfa(regexp);

	std::cout << start->to_string() << std::endl;

	reg_file.close();
}

std::string get_file_text(std::fstream &file)
{
	std::string str_out, line;

	while (file >> line)
	{
		str_out += line + " ";
	}
	str_out.pop_back();

	return str_out;
}

std::string convert_to_postfix_notation(std::string &exp)
{

	char operators_can_concat[] = {')', '[', '?', '*', '+'};
	std::string postfix;

	// Convert to expression with concatenations
	// bad code inside this for loop
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '\"')
		{

			if (std::find(std::begin(operators_can_concat), std::end(operators_can_concat), exp[i - 1]) !=
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

				while (!op_stack.empty())
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
