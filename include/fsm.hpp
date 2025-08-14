#pragma once 
#include <vector>
#include "state.hpp"
#include "behaviour.hpp"

class FiniteStateMachine : public Behaviour {
public:
	~FiniteStateMachine();
	void update(Agent* agent, float dtime);
	void addState(State* state);

private:
	std::vector<State*> m_states;
	State* m_currentState;
	State* m_newState;

};