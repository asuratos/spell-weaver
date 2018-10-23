#pragma once
#include "main.hpp"



Engine::Engine() : fovRad(20), computeFov(true) , gameState(START){
	TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(80, 50, "libtcodtutsv0.2", false);
	
	entL.emplace_back(std::make_shared<Ent>(1, 1, '@', "player", TCODColor::white));
	player = entL[0].get();
	
	dungeon = std::make_unique<Map>(80, 50);
}

Engine::~Engine() { entL.clear(); }

void Engine::update() {
	if (gameState == START) {
		dungeon->computeFov();
		gameState = IDLE;
	}

	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	int tx = 0, ty = 0;
	switch (key.vk) {
	case TCODK_CHAR:
		switch (key.c) {
		case 'k': ty = -1; break;
		case 'j': ty = 1; break;
		case 'h': tx = -1; break;
		case 'l': tx = 1; break;
		}
		break;
	case TCODK_UP: ty = 1; break;
	case TCODK_DOWN: ty = -1; break;
	case TCODK_LEFT: tx = -1; break;
	case TCODK_RIGHT: tx = 1; break;
	default: break;
	}

	if (tx != 0 || ty != 0) {
		gameState = TURN;
		if (player->moveOrAttack(player->x + tx, player->y + ty)) { dungeon->computeFov(); }
	}

	if (gameState == TURN){
		for (auto &ent : entL) { if (ent != entL[0]) { ent->update(); } }
	}

	if (computeFov) {
		dungeon->computeFov();
		computeFov = false;
	}

	gameState = IDLE;
}

void Engine::render() {
	TCODConsole::root->clear(); dungeon->render();
	
	for (auto &ent : entL) { if (dungeon->isInFov(ent->x, ent->y)) { ent->render(); } }
}