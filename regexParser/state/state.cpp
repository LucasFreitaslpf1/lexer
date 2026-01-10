#include "state.hpp"

int State::state_id = 1;

State::State(char _symb)
{
	this->id = State::state_id;
	State::state_id++;
	this->symbol = _symb;
}

std::string type_to_string(StateType t)
{
	switch (t)
	{
	case NOT_FINAL:
		return "NOT FINAL";
	case FINAL:
		return "FINAL";
	case INITIAL:
		return "INITIAL";
	}
}
