#include "selectorbehaviour.hpp"
#include "agent.hpp"

void SelectorBehaviour::update(Agent* agent, float dtime)
{
	if (glm::distance(agent->getPathAgent()->m_position, agent->getTarget()->getPathAgent()->m_position) < agent->getNodeMap()->m_cellSize * 5) {
		setBehaviour(m_b1, agent);
		agent->setColour({ 255, 0, 0, 255 });
	}
	else {
		setBehaviour(m_b2, agent);
		agent->setColour({ 255, 0, 255, 255 });
	}
	m_selected->update(agent, dtime);
}

SelectorBehaviour::~SelectorBehaviour()
{
	delete m_b1; 
	delete m_b2;
}

void SelectorBehaviour::setBehaviour(Behaviour* b, Agent* agent)
{
	if (m_selected != b) {
		m_selected = b;
		agent->reset();
	}
}


