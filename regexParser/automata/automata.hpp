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

	std::vector<std::pair<std::string, std::string>> match(std::string input);
	State *run(std::string input);
	void step(char c);
	void add_state(State *s, std::set<State *> &state_list);
	State *is_match();

	void clear();
};
