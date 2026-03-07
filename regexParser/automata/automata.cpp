#include "automata.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

bool Automata::run(std::string input)
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

bool Automata::is_match()
{

	for (auto &s : current_states)
	{
		if (s->type == FINAL)
		{
			return true;
		}
	}
	return false;
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
