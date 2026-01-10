#pragma once
#include <string>
#include <vector>
#define _FRAGMENT_HPP_
#include "../state/state.hpp"
enum FragType
{
	EXP,
	OP
};

std::string type_to_string(FragType t);
struct Fragment
{
	State *state = nullptr;
	FragType type;
	char op;

	std::vector<State **> pendent;

	std::vector<State *> initial_states;
	std::vector<State *> final_states;

	std::string to_string()
	{
		std::string s;
		if (state)
			s = state->to_string();

		return "Fragment: {" + type_to_string(type) + "\n" + s + "}";
	}

	void clear_final_states();
	void clear_initial_states();
	void add_initial_states(std::vector<State *> vec);
	void add_final_states(std::vector<State *> vec);

	void add_final_states(State *s);
	void add_initial_states(State *s);
	void add_pendent(State *s);

	void set_pendent(State *s);
};
