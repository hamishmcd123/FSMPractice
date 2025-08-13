#include "nodemap.hpp"
#include <iostream>
#include "raylib.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

Node* NodeMap::getNode(int x, int y)
{
	return m_nodes[x + m_width * y];
}

void NodeMap::draw()
{
	// Draw a solid rectangle where there ISN'T a node.
	Color cellColour{ 105, 105, 105, 255 };

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = getNode(x, y);
			if (node == nullptr) {
				DrawRectangle(static_cast<int>(x * m_cellSize), static_cast<int>(y * m_cellSize),
					static_cast<int>(m_cellSize), static_cast<int>(m_cellSize), cellColour);

			}
			else {
				for (int i = 0; i < node->connections.size(); i++) {
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5) * m_cellSize, (y + 0.5) * m_cellSize,
						static_cast<int>(other->position.x), static_cast<int>(other->position.y), BLACK);
				}
			}
		}
	}
}

void NodeMap::drawPath(std::vector<Node*> path)
{
	for (int i = 1; i < path.size(); i++) {
		DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x,
			path[i]->position.y, LIME);
	}
}


NodeMap::~NodeMap()
{
	if (m_nodes != nullptr) {
		for (int i = 0; i < m_width * m_height; i++) {
			delete m_nodes[i];
		}
	}
	delete[] m_nodes;
}

Node* NodeMap::getClosestNode(glm::vec2 worldPos)
{
	int i = (int)(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;
	
	int j = (int)(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_height) return nullptr;

	return getNode(i, j);
}

void NodeMap::initialise(std::vector<std::string>& asciiMap, int cellSize) {
	m_cellSize = cellSize;
	const char emptySquare = '0';
	m_height = asciiMap.size();

	// We are assuming all strings are the same length, so we set the width to the size of the first string.
	m_width = asciiMap[0].size();

	m_nodes = new Node*[m_width * m_height];

	for (int y = 0; y < m_height; y++) {
		std::string& line = asciiMap[y];
		
		if (line.size() != m_width) {
			std::cerr << "Mismatched line # " << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
		}
		
		for (int x = 0; x < m_width; x++) {
			char tile = x < line.size() ? line[x] : emptySquare;
			
			m_nodes[x + m_width * y] = tile == emptySquare ? nullptr :
				new Node((static_cast<float>(x) + 0.5f) * m_cellSize, (static_cast<float>(y) + 0.5f) * m_cellSize);

		}
	}

	// Loop over all nodes and create connections with the node south and west of it. 

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = getNode(x, y);
			if (node) {
				// See if there is a node to our west. Return nullptr if we are on the 
				// first node horizontally.
				Node* nodeWest = x == 0 ? nullptr : getNode(x - 1, y);
				if (nodeWest) {
					// Assuming a weight of 1 for now.
					node->connectTo(nodeWest, 1);
					nodeWest->connectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : getNode(x, y - 1);
				if (nodeSouth) {
					node->connectTo(nodeSouth, 1);
					nodeSouth->connectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::resetNodes()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* toReset = getNode(x, y);
			if (toReset) {
				toReset->previous = nullptr;
				toReset->gScore = FLT_MAX;
			}
		}
	}
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	if (startNode == nullptr || endNode == nullptr) {
		return {};
	}

	// Empty path if startNode = endNode
	if (startNode == endNode) {
		return {};
	}

	startNode->gScore = 0;
	startNode->previous = nullptr;

	// Create a comparison functor 
	struct Compare {
		bool operator()(Node* a, Node* b) {
			return a->gScore > b->gScore;
		}
	};

	// Create our open and closed list (priority queue custom comparison object)
	std::priority_queue<Node*, std::vector<Node*>, Compare> openList;
	std::unordered_set<Node*> openSet;
	std::unordered_set<Node*> closedList;

	openList.push(startNode);
	openSet.insert(startNode);

	while (!openList.empty()) {
		Node* currentNode = openList.top();

		if (currentNode == endNode) {
			break;
		}

		openList.pop();
		openSet.erase(currentNode);
		closedList.insert(currentNode);

		for (auto& c : currentNode->connections) {
			if (closedList.find(c.target) == closedList.end()) {
				int gScore = c.cost + currentNode->gScore;

			// If the target is not in the open list.
				if (openSet.find(c.target) == openSet.end()) {
					c.target->gScore = gScore;
					c.target->previous = currentNode;
					openList.push(c.target);
					openSet.insert(c.target);
				}
				else if (gScore < c.target->gScore){
					c.target->gScore = gScore;
					c.target->previous = currentNode;
					// To update priority queue.
					openList.push(c.target);
				}
			}
		}
	}

	std::vector<Node*> path;
	Node* currentNode = endNode;

	if (endNode->previous == nullptr) {
		return {};
	}

	while (currentNode != nullptr) {
		path.push_back(currentNode);
		currentNode = currentNode->previous;
	}
	std::reverse(path.begin(), path.end());

	return path;
}

Node* NodeMap::getRandomNode()
{
	Node* node = nullptr;
	while (node == nullptr)
	{
		int x = rand() % m_width;
		int y = rand() % m_height;
		node = getNode(x, y);
	}
	return node;
}
