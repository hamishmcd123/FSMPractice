#include "timecondition.hpp"

#include "agent.hpp"

TimerCondition::TimerCondition(float time) : m_time(time) {}

bool TimerCondition::isTrue(Agent *agent) {
    return *(agent->getStateTimer()) > m_time;
}
