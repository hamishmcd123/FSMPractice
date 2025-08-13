#include "wanderingbehaviour.hpp"
#include "agent.hpp"

void WanderBehaviour::update(Agent* agent, float dtime)
{
	if (agent->pathComplete()) {
		Node* newEnd = agent->getNodeMap()->getRandomNode();
		agent->goTo(newEnd->position);
	}
}

void WanderBehaviour::enter(Agent* agent)
{
	agent->setColour({ 0, 255, 255, 255 });
	agent->reset();
}
