#pragma once
#define _AUTOMATA_HPP_
#include "../state/state.hpp"

struct Automata
{
	State *state;

	bool run(std::string input);
};
