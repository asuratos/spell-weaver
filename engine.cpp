#include "main.hpp"

Engine::Engine() : fovRad(20), computeFov(true) {
	TCODConsole::initRoot(80, 50, "libtcodtutsv0.2", false);
	
	entL.emplace_back(std::make_shared<Ent>(1, 1, '@', TCODColor::white));
	player = entL[0].get();
	
	dungeon = std::make_unique<Map>(80, 50);
}

Engine::~Engine() { entL.clear(); }

void Engine::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	switch (key.vk) {
	case TCODK_CHAR:
		switch (key.c) {
		case 'k': if (!dungeon->isWall(player->x, player->y - 1)) { player->y--; computeFov = true;  }; break;
		case 'j':  if (!dungeon->isWall(player->x, player->y + 1)) { player->y++; computeFov = true;}; break;
		case 'h':  if (!dungeon->isWall(player->x - 1, player->y)) { player->x--; computeFov = true;}; break;
		case 'l': if (!dungeon->isWall(player->x + 1, player->y)) { player->x++; computeFov = true;}; break;
		}
		break;
	case TCODK_UP: if (!dungeon->isWall(player->x, player->y - 1)) { player->y--; computeFov = true;}; break;
	case TCODK_DOWN: if (!dungeon->isWall(player->x, player->y + 1)) { player->y++; computeFov = true;}; break;
	case TCODK_LEFT: if (!dungeon->isWall(player->x - 1, player->y)) { player->x--; computeFov = true;}; break;
	case TCODK_RIGHT: if (!dungeon->isWall(player->x + 1, player->y)) { player->x++; computeFov = true;}; break;
	default: break;

	}
	if (computeFov) {
		dungeon->computeFov();
		computeFov = false;
	}
}

void Engine::render() {
	TCODConsole::root->clear(); dungeon->render();
	
	for (auto &ent : entL) { ent->render(); }
}