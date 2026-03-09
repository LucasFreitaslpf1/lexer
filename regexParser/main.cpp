#include "automata/automata.hpp"
#include "parser/parser.hpp"
#include <iostream>
#include <string>

#include "parser/parser.hpp"

std::string regex_file = "lang.reg";

int main(int argc, char *argv[])
{
	std::string input, text;

	Automata automata;
	automata.state = parse_regex(regex_file);

	while (std::getline(std::cin, input))
	{
		text += input;
		text += "\n";
	}

	auto v = automata.match(text);
	automata.clear();

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].first[0] == '@')
			continue;
		std::cout << v[i].first << " " << v[i].second << "\n";
	}
	return 0;
}
