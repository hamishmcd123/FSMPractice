#include "followbehaviour.hpp"
#include "agent.hpp"

void FollowBehaviour::update(Agent* agent, float dtime)
{
	Agent* target = agent->getTarget();
	PathAgent* pa = agent->getPathAgent();
	float dist = glm::distance(pa->m_position, agent->m_lastTargetPosition);
	if (dist > agent->getNodeMap()->m_cellSize) {
		agent->m_lastTargetPosition = target->getPathAgent()->m_position;
		agent->goTo(agent->m_lastTargetPosition);
	}
}

void FollowBehaviour::enter(Agent* agent)
{
	agent->setColour(RED);
	agent->resetPath();
}
