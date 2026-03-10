#pragma once
#include <set>
#include <string_view>
#include <vector>
#define _AUTOMATA_HPP_
#include "../state/state.hpp"

struct Automata
{
	State *state;
	std::vector<State *> current_states;
	std::vector<State *> next_states;

	std::vector<std::pair<std::string, std::string>> match(std::string_view &input);
	State *run(std::string_view input);
	void step(char c);
	void add_state(State *s, std::vector<State *> &state_list);
	State *is_match();

	void clear();
};
