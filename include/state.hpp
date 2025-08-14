#pragma once
#include <vector>
#include "behaviour.hpp"
#include "condition.hpp"

class State {
public:
	struct Transition {
		Condition* condition;
		State* targetState;
	};

	State() = default;
	~State();
	virtual void update(Agent* agent, float dtime);
	virtual void enter(Agent* agent);
	virtual void exit(Agent* agent);
	std::vector<Transition*> getTransition();
	void addTransition(Condition* condition, State* targetState);
	void addBehaviour(Behaviour* behaviour);
private:
	std::vector<Behaviour*> m_behaviours;
	std::vector<Transition*> m_transitions; 
};