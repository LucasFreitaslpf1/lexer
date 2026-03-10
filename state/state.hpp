#pragma once
#include <string>
#define _STATE_HPP_

enum StateType
{
	NOT_FINAL,
	FINAL,
	INITIAL,
	SPLIT,
};

std::string type_to_string(StateType t);

struct State
{
	static int state_id;

	int id;
	char symbol;
	std::string token;

	State *out = nullptr;
	State *out_2 = nullptr;
	StateType type = NOT_FINAL;

	State(char _symb);

	std::string to_string()
	{
		std::string s1, s2;

		if (out)
		{
			s1 = out->to_string();
		}

		if (out_2)
		{
			s2 = out_2->to_string();
		}

		std::string s3 = "State: char: " + std::to_string(symbol) + " " + type_to_string(type) + "\n" +
						 "{\nout1:" + s1 + "\n" + "out2:" + s2 + "\n}";

		return s3;
	}

	void clear();
};
