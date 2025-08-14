#pragma once
#include "condition.hpp"

class TimerCondition : public Condition {
public:
    TimerCondition(float time);
    bool isTrue(Agent *agent) override;
    float m_time;
};


