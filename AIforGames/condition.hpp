#pragma once 
class Agent;

class Condition {
public:
	virtual bool isTrue(Agent* agent) = 0;
};

struct AND : public Condition{
	Condition* a;
	Condition* b;
	AND(Condition* a, Condition* b) : a(a), b(b) {}
	bool isTrue(Agent* agent) override { return a->isTrue(agent) && b->isTrue(agent); }
};