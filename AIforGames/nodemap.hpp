#pragma once
#include "pathfinding.hpp"
#include <vector>
#include <string>

class NodeMap{
public:
	int m_width; 
	int m_height;
	float m_cellSize;
	Node** m_nodes;
	Node* getNode(int x, int y);
	void draw();
	static void drawPath(std::vector<Node*> path);
	~NodeMap();
	Node* getClosestNode(glm::vec2 worldPos);
	void initialise(std::vector<std::string>& asciiMap, int cellSize);
	void resetNodes();
	static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	Node* getRandomNode();
};