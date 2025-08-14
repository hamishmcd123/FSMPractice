#include "fsm.hpp"

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : m_states) {
		delete s;
	}
}

void FiniteStateMachine::update(Agent* agent, float dtime)
{
	m_newState = nullptr;
	for (State::Transition* t : m_currentState->getTransition()) {
		if (t->condition->isTrue(agent)) {
			m_newState = t->targetState;
		}
	}

	if (m_newState != nullptr && m_newState != m_currentState) {
		m_currentState->exit(agent);
		m_newState->enter(agent);
		m_currentState = m_newState;
	}
	
	m_currentState->update(agent, dtime);
}

void FiniteStateMachine::addState(State* state)
{
	if (m_currentState == nullptr) {
		m_currentState = state;
	}

	m_states.push_back(state);
}
