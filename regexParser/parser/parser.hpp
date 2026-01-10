#pragma once
#include <vector>
#define _PARSER_HPP_

#include "../fragment/fragment.hpp"
#include <fstream>
#include <string>

State *parse_regex(std::string &s);
std::string get_file_text(std::fstream &file);
std::string convert_to_postfix_notation(std::string &exp);
State *build_nfa(std::string &regexp);
bool is_operator(char c);
void concatenation(std::vector<Fragment *> &stack, Fragment *frag);
void alternation(std::vector<Fragment *> &stack, Fragment *frag);
void zero_or_one(std::vector<Fragment *> &stack, Fragment *frag);
void one_or_more(std::vector<Fragment *> &stack, Fragment *frag);
void zero_or_more(std::vector<Fragment *> &stack, Fragment *frag);
