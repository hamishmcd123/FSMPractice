#include "wanderbehaviour.hpp"
#include "agent.hpp"

void WanderBehaviour::update(Agent* agent, float dtime)
{
	if (agent->pathComplete()) {
		PathAgent* pa = agent->getPathAgent();
		pa->goToNode(agent->getNodeMap()->getRandomNode());
	}
}

void WanderBehaviour::enter(Agent* agent)
{
	*(agent->getStateTimer()) += 0.0f;
	agent->getPathAgent()->setSpeed(100);
	agent->resetPath();
	agent->setColour(BLUE);
}

void WanderBehaviour::exit(Agent* agent)
{
	agent->resetPath();
}
