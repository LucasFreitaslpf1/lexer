#include "automata.hpp"
#include <vector>

bool Automata::run(std::string input)
{

	std::vector<State *> current_states;
	current_states.push_back(state);

	for (int i = 0; i < input.length(); i++)
	{
		std::vector<State *> next_states;
		while (!current_states.empty())
		{
			auto curr = current_states.back();
			current_states.pop_back();

			if (curr->symbol == input[i])
			{
				next_states.push_back(curr->out);
			}

			if (curr->symbol == ' ')
			{
				auto temp = curr;

				current_states.push_back(curr->out);

				if (curr->type == SPLIT)
				{
					current_states.push_back(curr->out_2);
				}
			}
		}

		current_states.insert(current_states.end(), next_states.begin(), next_states.end());
	}

	for (int i = 0; i < current_states.size(); i++)
	{
		if (current_states[i]->type == FINAL)
		{
			return true;
		}
	}
	return false;
}
