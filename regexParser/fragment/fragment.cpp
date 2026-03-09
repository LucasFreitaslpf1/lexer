#include "fragment.hpp"


void Fragment::set_pendent(State *s)
{
	for (int i = 0; i < pendent.size(); i++)
	{
		*pendent[i] = s;
	}

	pendent.clear();
}

void Fragment::add_pendent(State **s)
{
	pendent.push_back(s);
}

void Fragment::append_pendent(std::vector<State **> &pend)
{
	pendent.insert(pendent.begin(), pend.begin(), pend.end());
}
