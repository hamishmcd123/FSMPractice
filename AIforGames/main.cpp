#include <string>
#include "pathfinding.hpp"
#include "nodemap.hpp"
#include "raylib.h"
#include "pathagent.hpp"
#include "agent.hpp"
#include "fsm.hpp"
#include "wanderbehaviour.hpp"
#include "distancecondition.hpp"
#include "followbehaviour.hpp"
#include "recoverbehaviour.hpp"
#include "timecondition.hpp"
#include <iostream>
#include <ctime>

int main() {
	int cellSize = 32;
	srand((unsigned int)time(0));

	std::vector<std::string> asciiMap;
	asciiMap.push_back("000000000000000000000000000000");
	asciiMap.push_back("011111111111111111111111111110");
	asciiMap.push_back("011000000000001111000000000110");
	asciiMap.push_back("011011111110001001111111110110");
	asciiMap.push_back("011010000010001001000000010110");
	asciiMap.push_back("011011110011111001111110010110");
	asciiMap.push_back("011000010000001001000010010110");
	asciiMap.push_back("011111011111101111011110010110");
	asciiMap.push_back("010000010001000001000010010110");
	asciiMap.push_back("011111110111111111111110010110");
	asciiMap.push_back("011000000100000000000000010110");
	asciiMap.push_back("011011111101111111111111110110");
	asciiMap.push_back("011010000001000000000000000110");
	asciiMap.push_back("011011111101011111111111110110");
	asciiMap.push_back("011000000101000000000010000110");
	asciiMap.push_back("011111111101011111111111110110");
	asciiMap.push_back("011000000000000000000010000110");
	asciiMap.push_back("011111111111111111111111111110");
	asciiMap.push_back("000000000000000000000000000000");

	NodeMap map;
	map.initialise(asciiMap, cellSize);

	Node* start = map.getRandomNode();
	Node* end = nullptr;

	// Create distance condition
	// If the target is less than 8 cells away...
	DistanceCondition* lessThan6 = new DistanceCondition((float)(5 * map.m_cellSize), true);
	// If the target is more than 10 cells away...
	DistanceCondition* moreThan15 = new DistanceCondition((float)(15 * map.m_cellSize), false);

	// Create a time condition where chasing for 5 seconds leads to recovery state.
	TimerCondition* chaseFor4 = new TimerCondition(4.0f);

	// Create a time condition for recovering for 3 seconds.
	TimerCondition* recoverFor3 = new TimerCondition(3.0f);

	// Create finite state machine for npc.
	FiniteStateMachine* fsm = new FiniteStateMachine();

	// Create wander behaviour and state.
	WanderBehaviour* wanderBehaviour = new WanderBehaviour();
	State* wander = new State;

	// Create follow behaviour and state 
	FollowBehaviour* followBehaviour = new FollowBehaviour();
	State* follow = new State;

	// Create recover behaviour and state
	RecoverBehaviour* recoverBehaviour = new RecoverBehaviour();
	State* recover = new State;

	wander->addBehaviour(wanderBehaviour);
	wander->addTransition(lessThan6, follow);

	follow->addTransition(moreThan15, wander);
	follow->addTransition(chaseFor4, recover);
	follow->addBehaviour(followBehaviour);

	recover->addBehaviour(recoverBehaviour);
	recover->addTransition(new AND(recoverFor3, lessThan6), follow);
	recover->addTransition(new AND(recoverFor3, moreThan15), wander);

	fsm->addState(wander);
	fsm->addState(follow);
	fsm->addState(recover);

	Agent player(&map);
	PathAgent* playerPathAgent = player.getPathAgent();
	playerPathAgent->setNode(start);
	playerPathAgent->m_position = start->position;
	playerPathAgent->setSpeed(256);
	playerPathAgent->setRadius(10);

	start = map.getRandomNode();

	Agent npc(&map, fsm);
	PathAgent* npcPathAgent = npc.getPathAgent();
	npcPathAgent->setNode(start);
	npcPathAgent->m_position = start->position;
	npcPathAgent->setSpeed(100);
	npcPathAgent->setRadius(10);
	npc.setColour(BLUE);
	npc.setTarget(&player);

	std::vector<Node*> path = NodeMap::DijkstrasSearch(start, end);

	InitWindow(cellSize * map.m_width, cellSize * map.m_height, "NodeGraph");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		map.draw();
		NodeMap::drawPath(playerPathAgent->m_path, RAYWHITE);
		NodeMap::drawPath(npcPathAgent->m_path, npc.getColour());
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			map.resetNodes();
			Vector2 mousePos = GetMousePosition();
			start = map.getClosestNode(glm::vec2(mousePos.x, mousePos.y));
			path = NodeMap::DijkstrasSearch(start, end);
			if (start != nullptr) {
				playerPathAgent->setNode(start);
				playerPathAgent->m_position = start->position;
				playerPathAgent->goToNode(end);
			}
		}

		else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
			map.resetNodes();
			Vector2 mousePos = GetMousePosition();
			end = map.getClosestNode(glm::vec2(mousePos.x, mousePos.y));
			start = playerPathAgent->m_currentNode;
			playerPathAgent->goToNode(end);
		}
		map.drawStartEndNodes(start, end);
		npc.update(GetFrameTime());
		npc.draw();
		player.update(GetFrameTime());
		player.draw();
		EndDrawing();
	}

	CloseWindow();

}

