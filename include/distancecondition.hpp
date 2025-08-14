#pragma once
#include "condition.hpp"

class Agent;

class DistanceCondition : public Condition {
public:
	bool isTrue(Agent* agent) override;
	DistanceCondition(float distance, bool lessThan) : m_distance(distance), m_lessThan(lessThan) {}
private:
	float m_distance;
	bool m_lessThan;
};