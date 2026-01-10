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

	std::string to_string()
	{
		std::string s;
		if (state)
			s = state->to_string();

		return "Fragment: {" + type_to_string(type) + "\n" + s + "}";
	}
};
