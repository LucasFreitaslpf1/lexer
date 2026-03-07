#include "parser.hpp"
#include <csignal>
#include <vector>

State *build_nfa(std::string &regexp)
{
	for (int i = 0; i < regexp.size(); i++)
	{
		if (regexp[i] == '\0')
			regexp.erase(i, 1);
	}

	std::vector<Fragment *> stack;
	char empty = ' ';

	for (int i = 0; i < regexp.size(); i++)
	{
		Fragment *frag = new Fragment();
		switch (regexp[i])
		{
		case '*':
			zero_or_more(stack, frag);
			break;
		case '+':
			one_or_more(stack, frag);
			break;
		case '|':
			alternation(stack, frag);
			break;
		case '.':
			concatenation(stack, frag);
			break;
		case '?':
			zero_or_one(stack, frag);
			break;
		default:
			State *s = new State(regexp[i]);
			s->type = NOT_FINAL;

			frag->state = s;
			frag->p = &s->out;
			frag->pendent.push_back(&s->out);

			stack.push_back(frag);
		}
	}

	auto frag = stack.back();

	State *final = new State(' ');
	final->type = FINAL;

	frag->set_pendent(final);

	return frag->state;
}

void concatenation(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f2 = stack.back();
	stack.pop_back();
	Fragment *f1 = stack.back();
	stack.pop_back();

	f1->set_pendent(f2->state);
	f1->p = &f2->state;

	if (f2->state->type == FINAL)
		f2->state->type = NOT_FINAL;

	frag->state = f1->state;
	frag->pendent = f2->pendent;
	frag->p = f2->p;

	stack.push_back(frag);
}

void alternation(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f2 = stack.back();
	stack.pop_back();
	Fragment *f1 = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = SPLIT;

	s->out = f1->state;
	s->out_2 = f2->state;

	if (f1->state->type == FINAL)
		f1->state->type = NOT_FINAL;

	if (f2->state->type == FINAL)
		f2->state->type = NOT_FINAL;

	frag->state = s;
	frag->append_pendent(f1->pendent);
	frag->append_pendent(f2->pendent);

	stack.push_back(frag);
}

void zero_or_one(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = SPLIT;

	if (f->state->type == FINAL)
		f->state->type = NOT_FINAL;

	s->out = f->state;
	frag->state = s;

	frag->append_pendent(f->pendent);
	frag->add_pendent(&s->out_2);

	stack.push_back(frag);
}

void one_or_more(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = SPLIT;

	s->out = f->state;

	f->set_pendent(s);

	frag->state = f->state;
	frag->add_pendent(&s->out_2);

	stack.push_back(frag);
}

void zero_or_more(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = SPLIT;

	if (f->state->type == FINAL)
		f->state->type = NOT_FINAL;

	s->out = f->state;
	f->set_pendent(s);

	frag->state = s;
	frag->add_pendent(&s->out_2);

	stack.push_back(frag);
}
