#include "fragment.hpp"

std::string type_to_string(FragType t)
{
	switch (t)
	{
	case OP:
		return "OP";
	case EXP:
		return "EXP";
	}
}

void Fragment::clear_initial_states()
{
	for (int i = 0; i < initial_states.size(); i++)
	{
		initial_states[i]->type = NOT_FINAL;
	}

	initial_states.clear();
}
void Fragment::clear_final_states()
{

	for (int i = 0; i < final_states.size(); i++)
	{
		final_states[i]->type = NOT_FINAL;
	}

	final_states.clear();
}

void Fragment::add_initial_states(std::vector<State *> vec)
{
	initial_states.insert(initial_states.end(), vec.begin(), vec.end());
}

void Fragment::add_final_states(std::vector<State *> vec)
{
	final_states.insert(final_states.end(), vec.begin(), vec.end());
}

void Fragment::set_pendent(State *s)
{
	for (int i = 0; i < pendent.size(); i++)
	{
		*pendent[i] = s;
	}

	pendent.clear();
}

void Fragment::add_final_states(State *s)
{
	final_states.push_back(s);
}

void Fragment::add_initial_states(State *s)
{
	initial_states.push_back(s);
}

void Fragment::add_pendent(State *s)
{
	pendent.push_back(&s);
}
