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
			State *s1 = new State(regexp[i]);
			s1->type = INITIAL;
			State *s2 = new State(empty);
			s2->type = FINAL;

			s1->out = s2;
			frag->state = s1;

			frag->pendent.push_back(&s2->out);
			frag->final_states.push_back(s2);
			frag->initial_states.push_back(s1);
			stack.push_back(frag);
		}
	}

	return stack.back()->state;
}

void concatenation(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f2 = stack.back();
	stack.pop_back();
	Fragment *f1 = stack.back();
	stack.pop_back();

	f1->set_pendent(f2->state);

	f1->clear_final_states();
	f2->clear_initial_states();

	f2->state->type = NOT_FINAL;

	frag->state = f1->state;
	frag->pendent = f2->pendent;

	frag->add_final_states(f2->final_states);
	frag->add_initial_states(f1->initial_states);

	stack.push_back(frag);
}

void alternation(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f2 = stack.back();
	stack.pop_back();
	Fragment *f1 = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = INITIAL;

	State *s2 = new State(' ');
	s2->type = SPLIT;

	State *s3 = new State(' ');
	s3->type = FINAL;

	s->out = s2;

	s2->out = f1->state;
	f1->clear_initial_states();

	s2->out_2 = f2->state;
	f2->clear_initial_states();

	f1->set_pendent(s3);
	f2->set_pendent(s3);

	f1->clear_final_states();
	f2->clear_final_states();

	frag->state = s;
	frag->pendent.push_back(&s3->out);
	frag->initial_states.push_back(s);
	frag->final_states.push_back(s3);

	stack.push_back(frag);
}

void zero_or_one(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = INITIAL;

	State *s1 = new State(' ');
	s1->type = SPLIT;

	s->out = s1;

	State *s2 = new State(' ');
	s2->type = FINAL;

	s1->out = f->state;
	s1->out_2 = s2;

	f->set_pendent(s2);
	f->clear_initial_states();
	f->clear_final_states();

	frag->state = s;
	frag->add_pendent(s2->out);
	frag->add_initial_states(s);
	frag->add_final_states(s2);

	stack.push_back(frag);
}

void one_or_more(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = SPLIT;

	State *s1 = new State(' ');
	s1->type = FINAL;

	s->out = f->state;
	s->out_2 = s1;

	f->clear_final_states();
	f->set_pendent(s);

	frag->add_final_states(s1);
	frag->add_pendent(s1->out);
	frag->state = f->state;

	stack.push_back(frag);
}

void zero_or_more(std::vector<Fragment *> &stack, Fragment *frag)
{
	Fragment *f = stack.back();
	stack.pop_back();

	State *s = new State(' ');
	s->type = INITIAL;

	State *s1 = new State(' ');
	s1->type = SPLIT;

	State *s2 = new State(' ');
	s2->type = FINAL;

	s->out = s1;
	s1->out = f->state;
	s1->out_2 = s2;

	f->set_pendent(s1);
	f->clear_initial_states();
	f->clear_final_states();

	frag->state = s;
	frag->add_pendent(s2->out);
	frag->add_final_states(s2);

	stack.push_back(frag);
}
