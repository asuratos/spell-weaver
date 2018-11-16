#include "main.hpp"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::process(std::shared_ptr<Entity> ent){
	TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &engine.lastKey, NULL, false);
	
	int tx = 0, ty = 0;
	switch (engine.lastKey.vk) {
	case TCODK_CHAR:
		switch (engine.lastKey.c) {
		case 'k': ty = -1; break;
		case 'j': ty = 1; break;
		case 'h': tx = -1; break;
		case 'l': tx = 1; break;
		case 'z': break;
		}
		break;
	case TCODK_UP: ty = -1; break;
	case TCODK_DOWN: ty = 1; break;
	case TCODK_LEFT: tx = -1; break;
	case TCODK_RIGHT: tx = 1; break;
	default: break;
	}

	if (tx != 0 || ty != 0) {
		if (ent->ai->tryToMove(ent, ent->corporeal->loc.x + tx, ent->corporeal->loc.y + ty)) {
			engine.dungeon->computeFov();
		}
	}
}