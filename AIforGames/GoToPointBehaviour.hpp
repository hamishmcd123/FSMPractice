#pragma once 
#include "behaviour.hpp"

class GoToPointBehaviour : public Behaviour {
public:
	void update(Agent* agent, float dtime) override;
};