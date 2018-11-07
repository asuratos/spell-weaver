#include "main.hpp"

void InputHandler::process(){
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &engine.lastKey, NULL);
	
	switch (engine.lastKey.vk) {
	case (TCODK_CHAR):
		switch (engine.lastKey.c) {
		case 'h':break;
		case 'j':break;
		case 'k':break;
		case 'l':break;
		}
	}
}