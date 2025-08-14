#include "distancecondition.hpp"
#include "agent.hpp"

bool DistanceCondition::isTrue(Agent* agent)
{
    PathAgent* pa = agent->getPathAgent();
    Agent* target = agent->getTarget();
    PathAgent* targetPA = target->getPathAgent();
    return (glm::distance(pa->m_position, targetPA->m_position) < m_distance) == m_lessThan;
}
