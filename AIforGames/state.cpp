#include "state.hpp"
#include "behaviour.hpp"

State::State(Behaviour* behaviour)
{
	m_behaviours.push_back(behaviour);
}

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
		b->exit(agent);
	}
}

void State::addTransition(Condition* condition, State* target)
{
	m_transitions.push_back(new State::Transition{ condition, target });
}



std::vector<State::Transition*> State::getTransitions()
{
	return m_transitions;
}
