#pragma once
#include <string>
#include <vector>
#define _FRAGMENT_HPP_
#include "../state/state.hpp"

struct Fragment
{
	State *state = nullptr;
	char op;
	State *final = nullptr;
	std::vector<State **> pendent;

	void add_pendent(State **s);
	void set_pendent(State *s);
	void append_pendent(std::vector<State **> &pend);
};
