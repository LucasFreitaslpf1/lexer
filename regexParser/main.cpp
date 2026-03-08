#include "automata/automata.hpp"
#include "parser/parser.hpp"
#include <iostream>
#include <string>

#include "parser/parser.hpp"

// CONFIG VARS, THIS WILL BE KEPT AS GLOBAL VARIABLES FOR NOW UNTIL A CONFIG FILE IS CREATED

std::string regex_file = "lang.reg";

int main(int argc, char *argv[])
{

	std::string input, text;

	Automata automata;
	automata.state = parse_regex(regex_file);

	while (std::cin >> input)
	{
		text += input;
		text += " ";
	}

	auto v = automata.match(text);
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i].first << " " << v[i].second << "\n";
	}
	// std::cout << (s ? s->token + " " + input + "\n" : "");
	return 0;
}
