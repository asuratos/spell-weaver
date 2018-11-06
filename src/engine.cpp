#pragma once
#include "main.hpp"



Engine::Engine(int sW, int sH) : fovRad(20), computeFov(true) , sW(sW), sH(sH), gameState(START){
	//TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::setCustomFont("Raving_1280x400.bmp", TCOD_FONT_LAYOUT_ASCII_INROW);
	TCODConsole::initRoot(sW, sH, "libtcodtutsv0.6", false);
	
	player = std::make_shared<Ent>(1, 1, '@', "player", TCODColor::white);
	player->mortal = std::make_shared<pcMortal>(30, 2, "your lifeless corpse");
	player->combat = std::make_shared<Combat>(5);
	player->ai = std::make_shared<PlayerAi>();

	entL.push_back(player);
	
	dungeon = std::make_unique<Map>(80, 45);
}

Engine::~Engine() { entL.clear(); }//magicL.clear(); }

void Engine::update() {
	if (gameState == START) {
		dungeon->computeFov();
		gameState = IDLE;
	}

	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);

	player->update(player);
	/*
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
		if (player->moveOrAttack(player->loc.x + tx, player->loc.y + ty)) { dungeon->computeFov(); }
	}*/

	if (gameState == TURN) {
		for (auto &ent : entL) {
			if (ent->mortal) {
				if (ent->name != "player" && !ent->mortal->isDead()) { ent->update(ent); }
			}
		}
	}
	if (computeFov) {
		dungeon->computeFov();
		computeFov = false;
	}

	gameState = IDLE;
}


void Engine::render() {
	TCODConsole::root->clear(); dungeon->render();
	
	for (auto &ent : entL) { if (ent->mortal) { if (ent->mortal->isDead()) { if (dungeon->isInFov(ent->loc.x, ent->loc.y)) { ent->render(); } } } }

	for (auto &ent : entL) { if (ent->mortal) { if (!ent->mortal->isDead()) { if (dungeon->isInFov(ent->loc.x, ent->loc.y)) { ent->render(); } } } }

	player->render();

	static std::stringstream hpDisplay;

	hpDisplay.str(std::string());
	hpDisplay << std::setprecision(0) << "HP : " << player->mortal->hp << "/" << player->mortal->MaxHp;

	TCODConsole::root->print(1, sH - 2,  hpDisplay.str());
}