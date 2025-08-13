#pragma once

class Agent;

class Condition {
public:
	virtual bool isTrue(Agent* agent) = 0;
};