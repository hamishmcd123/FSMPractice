#pragma once 
#include "behaviour.hpp"

class SelectorBehaviour : public Behaviour {
public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
	void update(Agent* agent, float dtime) override;
	~SelectorBehaviour();
	void setBehaviour(Behaviour* b, Agent* agent);
private:
	Behaviour* m_b1;
	Behaviour* m_b2;
	Behaviour* m_selected;
};