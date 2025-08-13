#include "followbehaviour.hpp"
#include "agent.hpp"

void FollowBehaviour::update(Agent* agent, float dtime)
{
	Agent* target = agent->getTarget();
	float dist = glm::distance(target->getPathAgent()->m_position, agent->lastTargetPosition);
	if (dist > agent->getNodeMap()->m_cellSize) {
		agent->lastTargetPosition = target->getPathAgent()->m_position;
		agent->goTo(agent->lastTargetPosition);
	}
}

void FollowBehaviour::enter(Agent* agent)
{
	agent->setColour({ 255, 0, 0, 255 });
	agent->reset();
}
