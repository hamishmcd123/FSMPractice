#include "agent.hpp"

Agent::Agent(NodeMap* nodeMap, FiniteStateMachine* fsm)
{
	m_pathAgent = PathAgent();
	m_nodeMap = nodeMap;
	m_fsm = fsm;
	m_colour = { 255,255, 255, 255 };
	m_target = nullptr;
	m_lastTargetPosition = glm::vec2();
}

Agent::Agent(NodeMap* nodeMap)
{
	m_pathAgent = PathAgent();
	m_nodeMap = nodeMap;
	m_fsm = nullptr;
	m_colour = { 255,255, 255, 255 };
	m_target = nullptr;
	m_lastTargetPosition = glm::vec2();
}

PathAgent* Agent::getPathAgent()
{
	return &m_pathAgent;
}

bool Agent::pathComplete()
{
	return m_pathAgent.m_path.empty();
}

void Agent::draw()
{
	m_pathAgent.draw(m_colour);
}

void Agent::update(float dtime)
{
	if (m_fsm != nullptr) {
		m_fsm->update(this, dtime);
	}

	m_pathAgent.update(dtime);
}

NodeMap* Agent::getNodeMap()
{
	return m_nodeMap;
}

void Agent::resetPath()
{
	m_pathAgent.m_path.clear();
}

void Agent::setColour(Color colour)
{
	m_colour = colour;
}

void Agent::goTo(glm::vec2 point)
{
	Node* end = m_nodeMap->getClosestNode(point);
	m_pathAgent.goToNode(end);
}

void Agent::setTarget(Agent* target)
{
	m_target = target;
}

float* Agent::getStateTimer() {
	return &m_stateTimer;
}

Color Agent::getColour()
{
	return m_colour;
}

Agent* Agent::getTarget()
{
	return m_target;
}

Agent::~Agent()
{
	delete m_fsm;
}
