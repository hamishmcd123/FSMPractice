#include "followbehaviour.hpp"
#include "agent.hpp"

void FollowBehaviour::update(Agent* agent, float dtime)
{
	*agent->getStateTimer() += dtime;
	Agent* target = agent->getTarget();
	PathAgent* pa = target->getPathAgent();

	if ((agent->getPathAgent()->m_path.empty())) {
		agent->m_lastTargetPosition = target->getPathAgent()->m_position;
		agent->goTo(agent->m_lastTargetPosition);
		return;
	}

	float dist = glm::distance(pa->m_position, agent->m_lastTargetPosition);
	if (dist > agent->getNodeMap()->m_cellSize) {
		agent->m_lastTargetPosition = target->getPathAgent()->m_position;
		agent->goTo(agent->m_lastTargetPosition);
	}
}

void FollowBehaviour::enter(Agent* agent)
{
	agent->getPathAgent()->setSpeed(200);
	agent->setColour(RED);
	agent->resetPath();
}

void FollowBehaviour::exit(Agent *agent) {
	agent->resetPath();
}
