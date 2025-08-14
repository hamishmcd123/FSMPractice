#include "recoverbehaviour.hpp"
#include "agent.hpp"

void RecoverBehaviour::exit(Agent *agent) {
    agent->resetPath();
}

void RecoverBehaviour::update(Agent *agent, float dtime) {
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

void RecoverBehaviour::enter(Agent *agent) {
    *agent->getStateTimer() = 0.0f;
    agent->getPathAgent()->setSpeed(50);
    agent->setColour(YELLOW);
    agent->resetPath();
}
