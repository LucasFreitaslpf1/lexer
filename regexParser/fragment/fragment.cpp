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
