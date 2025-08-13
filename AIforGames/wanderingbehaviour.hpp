#pragma once
#include "behaviour.hpp"

class WanderBehaviour : public Behaviour {
public:
	void update(Agent* agent, float dtime) override;
	void enter(Agent* agent) override;


};
