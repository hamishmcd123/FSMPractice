#include "finitestatemachine.hpp"

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : m_states) {
		delete s;
	}
}

void FiniteStateMachine::update(Agent* agent, float dtime)
{

	State* newState = nullptr;

	for (State::Transition* t : m_currentState->getTransitions()) {
		if (t->condition->isTrue(agent)) {
			newState = t->targetState;
		}
	}

	if (newState != nullptr && newState != m_currentState) {
		m_currentState->exit(agent);
		m_currentState = newState;
		m_currentState->enter(agent);
	}

	m_currentState->update(agent, dtime);



}

void FiniteStateMachine::addState(State* state)
{
	m_states.push_back(state);
}
