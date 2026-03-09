#include "automata.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<std::string, std::string>> Automata::match(std::string input)
{
	std::vector<std::pair<std::string, std::string>> output;

	for (int i = 0; i < input.size(); i++)
	{
		State *last = nullptr;
		std::string last_substr = "";

		for (int j = i; j < input.size(); j++)
		{
			auto substr = input.substr(i, j - i + 1);
			State *s = run(substr);

			if (s)
			{
				if (substr.size() > last_substr.size())
				{
					last = s;
					last_substr = substr;
				}
			}
		}
		if (last)
		{
			output.push_back({last->token, last_substr});
			i = i + last_substr.size() - 1;
		}
	}

	return output;
}

State *Automata::run(std::string input)
{
	add_state(state, current_states);

	for (int i = 0; i < input.size(); i++)
	{
		step(input[i]);
		std::swap(current_states, next_states);

		next_states.clear();
	}

	return is_match();
}

State *Automata::is_match()
{
	State *ret = nullptr;
	for (auto s : current_states)
	{
		if (s->type == FINAL)
		{
			ret = s;
			break;
		}
	}
	current_states.clear();
	return ret;
}

void Automata::step(char c)
{
	for (auto s : current_states)
	{
		if (s->symbol == c)
		{
			add_state(s->out, next_states);
		}
	}
}
void Automata::add_state(State *s, std::set<State *> &state_list)
{
	if (!s)
		return;

	if (s->type == SPLIT)
	{
		add_state(s->out, state_list);
		add_state(s->out_2, state_list);
		return;
	}

	state_list.insert(s);
}

void Automata::clear()
{
	std::vector<State *> states;
	std::stack<State *> stack;

	stack.push(state);

	while (!stack.empty())
	{
		auto curr = stack.top();
		stack.pop();

		if (std::find(states.begin(), states.end(), curr) == states.end())
		{
			states.push_back(curr);

			if (curr->out)
				stack.push(curr->out);

			if (curr->out_2)
				stack.push(curr->out_2);
		}
	}

	for (State *s : states)
	{
		delete s;
	}
}
