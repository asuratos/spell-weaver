#include "main.hpp"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::takeTurn(const std::shared_ptr<Entity>& ent){
	TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &engine.lastKey, NULL, true);
	
	int tx = 0, ty = 0;
	switch (engine.lastKey.vk) {
	case TCODK_CHAR:
		switch (engine.lastKey.c) {
		//movement-related
		case 'k': ty = -1; break;
		case 'j': ty = 1; break;
		case 'h': tx = -1; break;
		case 'l': tx = 1; break;
		case 'z': break;

		//channeling-related 
		case 'q': ent->caster->channel(Caster::FIRE, ent); break;
		case 'w': ent->caster->channel(Caster::EARTH, ent); break;
		case 'a': ent->caster->channel(Caster::AIR, ent); break;
		case 's': ent->caster->channel(Caster::WATER, ent); break;
		case 'e': ent->caster->channel(Caster::SPIRIT, ent); break;
		case 'd': ent->caster->release(); break;
		case 'r': engine.Magic->castSpell(ent);  break;
		}
		break;
	case TCODK_UP: ty = -1; break;
	case TCODK_DOWN: ty = 1; break;
	case TCODK_LEFT: tx = -1; break;
	case TCODK_RIGHT: tx = 1; break;
	//default: break;
	}

	if (tx != 0 || ty != 0) {
		if (ent->ai->tryToMove(ent, ent->spatial->loc.x + tx, ent->spatial->loc.y + ty)) {
			engine.dungeon->computeFov();
		}
		//engine.gui->message(std::string("Step"), TCODColor::white);
	}
}