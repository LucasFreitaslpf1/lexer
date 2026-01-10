#include "automata/automata.hpp"
#include "parser/parser.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include "parser/parser.hpp"

// CONFIG VARS, THIS WILL BE KEPT AS GLOBAL VARIABLES FOR NOW UNTIL A CONFIG FILE IS CREATED

std::string regex_file = "lang.reg";

int main(int argc, char *argv[])
{
	// if (argc < 2)
	// {
	// 	std::cerr << "Input file needed!";
	// 	return -1;
	// }
	Automata automata;
	automata.state = parse_regex(regex_file);

	std::cout << (automata.run("abab") ? "Sim" : "Não") << std::endl;
	return 0;
}
