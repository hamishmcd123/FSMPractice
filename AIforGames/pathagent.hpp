#pragma once
#include "pathfinding.hpp"
#include "raylib.h"

class PathAgent {
public:
	Node* m_currentNode;
	float m_speed;
	int m_currentIndex;
	std::vector<Node*> m_path;
	glm::vec2 m_position;
	int m_radius;
	void update(float dtime);
	void goToNode(Node* node);
	void draw(Color colour) const;
	void setNode(Node* node);
	void setSpeed(int speed);
	void setRadius(int radius);
};