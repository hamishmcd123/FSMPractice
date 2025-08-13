#pragma once 
#include "condition.hpp"

class DistanceCondition : public Condition {
public:
	DistanceCondition(float distance, bool lessThan) : m_distance(distance), m_lessThan(lessThan) {}
	bool isTrue(Agent* agent) override;
private:
	float m_distance;
	bool m_lessThan;
};