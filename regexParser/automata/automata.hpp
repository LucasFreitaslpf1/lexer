#pragma once
#include <set>
#include <vector>
#define _AUTOMATA_HPP_
#include "../state/state.hpp"

struct Automata
{
	State *state;
	std::set<State *> current_states;
	std::set<State *> next_states;

	bool run(std::string input);
	void step(char c);
	void add_state(State *s, std::set<State *> &state_list);
	bool is_match();
	void handle_empty_state(State *s, std::set<State *> &empty_states, char c);
};
