#pragma once
#include <glm/glm.hpp>
#include <vector>
struct Node;

struct Edge {
	Edge() { target = nullptr; cost = 0; }
	Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
	Node* target;
	float cost;
};

struct Node {
	glm::vec2 position;
	std::vector<Edge> connections;
	Node(float xpos, float ypos) : position(glm::vec2(xpos, ypos)) { previous = nullptr; gScore = FLT_MAX; }
	float gScore;
	Node* previous;
	void connectTo(Node* other, float cost);
};
