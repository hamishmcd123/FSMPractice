#include "agent.hpp"
#include "behaviour.hpp"

Agent::~Agent()
{
	delete m_current;
}

void Agent::update(float dtime)
{
	if (m_current) {
		m_current->update(this, dtime);
	}
	if (fsm) {
		fsm->update(this, dtime);
	}
	m_pathAgent.update(dtime);
}

void Agent::draw()
{
	m_pathAgent.draw(m_colour);
}

void Agent::goTo(glm::vec2 point)
{
	Node* end = m_nodeMap->getClosestNode(point);
	m_pathAgent.goToNode(end);

}

PathAgent* Agent::getPathAgent()
{
	return &m_pathAgent;
}

NodeMap* Agent::getNodeMap()
{
	return m_nodeMap;
}

bool Agent::pathComplete()
{
	return m_pathAgent.m_path.empty();
}

Agent* Agent::getTarget()
{
	return m_target;
}

void Agent::setTarget(Agent* agent)
{
	m_target = agent;
}

void Agent::setColour(Color _colour)
{
	m_colour = _colour;
}

void Agent::reset()
{
	m_pathAgent.m_path.clear();
}


