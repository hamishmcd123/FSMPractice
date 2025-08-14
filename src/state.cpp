#include "state.hpp"

State::~State()
{
	for (Behaviour* b : m_behaviours) {
		delete b;
	}

	for (Transition* t : m_transitions) {
		delete t->condition;
	}
}

void State::update(Agent* agent, float dtime)
{
	for (Behaviour* b : m_behaviours) {
		b->update(agent, dtime);
	}
}

void State::enter(Agent* agent)
{
	for (Behaviour* b : m_behaviours) {
		b->enter(agent);
	}
}

void State::exit(Agent* agent)
{
	for (Behaviour* b : m_behaviours) {
		b->enter(agent);
	}
}

std::vector<State::Transition*> State::getTransition()
{
	return m_transitions;
}

void State::addTransition(Condition* condition, State* targetState)
{
	m_transitions.push_back(new State::Transition{ condition, targetState });
}

void State::addBehaviour(Behaviour* behaviour)
{
	m_behaviours.push_back(behaviour);
}
