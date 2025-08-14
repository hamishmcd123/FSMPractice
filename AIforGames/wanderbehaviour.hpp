#pragma once
#include "behaviour.hpp"

class WanderBehaviour : public Behaviour {
	void update(Agent* agent, float dtime) override;
	void enter(Agent* agent) override;
	void exit(Agent* agent) override;
};
