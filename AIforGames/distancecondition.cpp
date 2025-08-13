#include "distancecondition.hpp"
#include "agent.hpp"

bool DistanceCondition::isTrue(Agent* agent)
{
	return (glm::distance(agent->getPathAgent()->m_position, agent->getTarget()->getPathAgent()->m_position) < m_distance)== m_lessThan;
}
