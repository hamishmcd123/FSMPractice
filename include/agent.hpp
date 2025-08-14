#pragma once
#include "pathagent.hpp"
#include "nodemap.hpp"
#include "fsm.hpp"
#include "raylib.h"

class Agent {
public:
	Agent(NodeMap* nodeMap, FiniteStateMachine* fsm);
	Agent(NodeMap* nodeMap);
	PathAgent* getPathAgent();
	bool pathComplete();
	void draw();
	void update(float dtime);
	NodeMap* getNodeMap();
	void resetPath();
	void setColour(Color colour);
	void goTo(glm::vec2 point);
	void setTarget(Agent* target);
	float* getStateTimer();
	Color getColour();
	glm::vec2 m_lastTargetPosition;
	Agent* getTarget();
private:
	PathAgent m_pathAgent;
	NodeMap* m_nodeMap;
	FiniteStateMachine* m_fsm;
	Color m_colour;
	Agent* m_target;
	float m_stateTimer;
};
