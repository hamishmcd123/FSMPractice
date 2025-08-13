#pragma once
#include "behaviour.hpp"

class FollowBehaviour : public Behaviour {
	void update(Agent* agent, float dtime) override;
	void enter(Agent* agent) override;
};