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

void Automata::handle_empty_state(State *s, std::set<State *> &empty_states, char c)
{
	if (!s)
		return;

	if (s->symbol == ' ' && s->type != FINAL)
	{
		if (empty_states.find(s) != empty_states.end())
		{
			return;
		}

		if (s->out && s->out->type == FINAL)
		{
			next_states.insert(s->out);
		}

		if (s->out_2 && s->out_2->type == FINAL)
		{
			next_states.insert(s->out_2);
		}

		empty_states.insert(s);
		handle_empty_state(s->out, empty_states, c);
		handle_empty_state(s->out_2, empty_states, c);

		return;
	}

	current_states.insert(s);
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
