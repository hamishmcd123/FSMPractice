#pragma once 
#include "behaviour.hpp"
#include "state.hpp"
#include <vector>


class FiniteStateMachine : public Behaviour {
public:
	FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
	virtual ~FiniteStateMachine();
	void update(Agent* agent, float dtime);
	void addState(State* state);

private:
	std::vector<State*> m_states;
	State* m_currentState;
	State* m_newState;
};