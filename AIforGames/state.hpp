#pragma once 
#include <vector>
#include "condition.hpp"

class Behaviour;
class Agent;

class State {
public:
	struct Transition {
		Condition* condition;
		State* targetState;
	};

	State(Behaviour* behaviour);
	~State();
	virtual void update(Agent* agent, float dtime);
	virtual void enter(Agent* agent);
	virtual void exit(Agent* agent);
	void addTransition(Condition* condition, State* target);
	std::vector<Transition*> getTransitions();
private:
	std::vector<Behaviour*> m_behaviours;
	std::vector<Transition*> m_transitions;
	};