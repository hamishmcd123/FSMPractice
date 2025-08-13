#pragma once 

class Agent; 

class Behaviour {
public:
	virtual void update(Agent* agent, float dtime) = 0;
	virtual void enter(Agent* agent) {}
	virtual void exit(Agent*) {}
};