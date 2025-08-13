#include <string>
#include <ctime>
#include "pathfinding.hpp"
#include "nodemap.hpp"
#include "raylib.hpp"
#include "pathagent.hpp"
#include "agent.hpp"
#include "GoToPointBehaviour.hpp"
#include "wanderingbehaviour.hpp"
#include "followbehaviour.hpp"
#include "selectorbehaviour.hpp"
#include "finitestatemachine.hpp"
#include "distancecondition.hpp"

int main() {
    int cellSize = 32;
    srand(time(0));

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
    
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f * map.m_cellSize, true);
    DistanceCondition* furtherThan7 = new DistanceCondition(7.0f * map.m_cellSize, false);
    
    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());

    wanderState->addTransition(closerThan5, followState);
    followState->addTransition(furtherThan7, wanderState);

    FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    fsm->addState(wanderState);
    fsm->addState(followState);

    Agent agent(&map, new GoToPointBehaviour());
    Agent agent2(&map, fsm);

    agent.getPathAgent()->setNode(start);
    agent.getPathAgent()->m_position = start->position;
    agent.getPathAgent()->setSpeed(200);
    agent.getPathAgent()->setRadius(10);
    agent.setColour({ 255, 255, 255, 255 });

    start = map.getRandomNode();

    agent2.getPathAgent()->setNode(start);
    agent2.getPathAgent()->m_position = start->position;
    agent2.getPathAgent()->setSpeed(100);
    agent2.getPathAgent()->setRadius(10);
    agent2.setTarget(&agent);
    agent2.setColour({ 0, 255, 255, 255 });

   InitWindow(cellSize * map.m_width, cellSize * map.m_height, "NodeGraph");

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginDrawing();
        ClearBackground(BLACK);
        map.draw();
        NodeMap::drawPath(agent.getPathAgent()->m_path);
        agent.update(GetFrameTime());
        agent2.update(GetFrameTime());
        agent.draw();
        agent2.draw();
        EndDrawing();
    }

    CloseWindow();
    
}

