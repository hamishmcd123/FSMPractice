#include "GoToPointBehaviour.hpp"
#include "agent.hpp"

void GoToPointBehaviour::update(Agent* agent, float dtime)
{

	NodeMap* map = agent->getNodeMap();

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Vector2 mousePos = GetMousePosition();
		agent->goTo(glm::vec2(mousePos.x, mousePos.y));
	}

}
