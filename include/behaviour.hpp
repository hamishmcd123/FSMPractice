#pragma once

class Agent;

class Behaviour {
public:
	virtual void enter(Agent* agent){}
	virtual void update(Agent* agent, float dtime) = 0;
	virtual void exit(Agent* agent) {}
};