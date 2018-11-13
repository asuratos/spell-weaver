#pragma once
#include "main.hpp"



Engine::Engine(int sW, int sH) : fovRad(20), computeFov(true) , sW(sW), sH(sH), gameState(START){
	//TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::setCustomFont("Raving_1280x400.bmp", TCOD_FONT_LAYOUT_ASCII_INROW);
	TCODConsole::initRoot(sW, sH, "libtcodtutsv0.6", false);

	Mover = std::make_unique<MovementSystem>();
	
	std::shared_ptr<Entity> player = std::make_shared<Entity>(std::string("player"), Entity::ACTOR);
	player->isPlayer = true;

	player->corporeal = std::make_shared<Corporeal>(coords(1, 1), true);
	player->mortal = std::make_shared<Mortal>(30, 2, "your lifeless corpse");
	player->combat = std::make_shared<Combat>(5);
	player->input = std::make_shared<InputHandler>();
	player->clock = std::make_shared<Clock>(10);

	entL.push_back(player);
	
	dungeon = std::make_unique<Map>(80, 45);
}

Engine::~Engine() { entL.clear(); }

void Engine::update() {
	if (gameState == START) {
		dungeon->computeFov();
		render();
		gameState = GAME;
	}
	if (gameState == GAME){
		for (auto &ent : entL) {
			std::shared_ptr<Actor> ent = static_cast<std::shared_ptr<Actor>>(ent);
			if (ent->clock) {
				if (!ent->mortal->isDead()) { 
					ent->clock->increment();
					if (ent->clock->isReady()) {
						ent->update(ent);
					}
				}
			}
		}
	}
	if (computeFov) {
		dungeon->computeFov();
		computeFov = false;
	}

}


void Engine::render() {
	TCODConsole::root->clear(); 
	dungeon->render();
	
	for (auto &ent : entL) { 
		if (ent->clock) { 
			if (dungeon->isInFov(ent->loc.x, ent->loc.y)) { 
				ent->render(); 
			} 
		}
	}
	/*
	for (auto &ent : entL) { 
		if (ent->mortal) { 
			if (!ent->mortal->isDead()) { 
				if (dungeon->isInFov(ent->loc.x, ent->loc.y)) { 
					ent->render(); } 
			}
		}
	}
	*/
	player->render();

	static std::stringstream hpDisplay;

	hpDisplay.str(std::string());
	hpDisplay << std::setprecision(0) << "HP : " << player->mortal->hp << "/" << player->mortal->MaxHp;

	TCODConsole::root->print(1, sH - 2,  hpDisplay.str());
}