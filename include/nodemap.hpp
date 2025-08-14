#pragma once
#include "pathfinding.hpp"
#include <vector>
#include <string>
#include "raylib.h"

class NodeMap{
public:
	int m_width; 
	int m_height;
	int m_cellSize;
	Node** m_nodes;
	Node* getNode(int x, int y);
	void draw();
	static void drawPath(std::vector<Node*> path, Color colour);
	~NodeMap();
	Node* getClosestNode(glm::vec2 worldPos);
	Node* getRandomNode();
	void initialise(std::vector<std::string>& asciiMap, int cellSize);
	void resetNodes();
	void drawStartEndNodes(Node* startNode, Node* endNode);
	static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
};