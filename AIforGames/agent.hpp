#pragma once 
#include "nodemap.hpp"
#include "pathagent.hpp"
#include "raylib.h"
#include "finitestatemachine.hpp"

class Behaviour;

class Agent {
public:
	Agent() {}
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_colour({ 255, 255, 0, 255 }) {}
	Agent(NodeMap* _nodeMap, FiniteStateMachine* _fsm) : m_nodeMap(_nodeMap), m_colour({ 255, 255, 0, 255 }), fsm(_fsm) {}
	~Agent();
	void update(float dtime);
	void draw();
	void goTo(glm::vec2 point);
	PathAgent* getPathAgent();
	NodeMap* getNodeMap();
	bool pathComplete();
	Agent* getTarget();
	void setTarget(Agent* agent);
	void setColour(Color _colour);
	glm::vec2 lastTargetPosition;
	void reset();
private:
	PathAgent m_pathAgent; 
	Behaviour* m_current; 
	NodeMap* m_nodeMap;
	Color m_colour;
	Agent* m_target;
	FiniteStateMachine* fsm;
};