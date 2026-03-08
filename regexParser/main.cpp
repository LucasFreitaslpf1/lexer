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

	while (std::getline(std::cin, input))
	{
		text += input;
		text += " ";
	}

	Automata automata;
	automata.state = parse_regex(regex_file);

	std::cout << (automata.run(text) ? "Sim" : "Não") << std::endl;
	return 0;
}
