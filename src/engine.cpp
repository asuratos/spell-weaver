#pragma once
#include "main.hpp"



Engine::Engine(int sW, int sH) : fovRad(20), computeFov(true) , sW(sW), sH(sH), gameState(START){
	//TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::setCustomFont("Raving_1280x400.bmp", TCOD_FONT_LAYOUT_ASCII_INROW);
	TCODConsole::initRoot(sW, sH, "libtcodtutsv0.6", false);

	
	player = std::make_shared<Entity>(std::string("player"), Entity::ACTOR);
	
	player->isPlayer = true;
	player->ai = std::make_shared<PlayerAi>();
	player->disp = std::make_shared<DisplayComponent>('@', TCODColor::white);
	player->spatial = std::make_shared<Spatial>(coords(1, 1), true);
	player->mortal = std::make_shared<Mortal>(30, 2, "your lifeless corpse");
	player->combat = std::make_shared<Combat>(5);
	player->input = std::make_shared<InputHandler>();
	player->clock = std::make_shared<Clock>(10);

	entL.push_back(player);

	Mover = std::make_unique<MovementSystem>();
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
			if (dungeon->isInFov(ent->spatial->loc.x, ent->spatial->loc.y)) { 
				ent->disp->render(ent); 
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
	player->disp->render(player);

	static std::stringstream hpDisplayComponent;

	hpDisplayComponent.str(std::string());
	hpDisplayComponent << std::setprecision(0) << "HP : " << player->mortal->hp << "/" << player->mortal->MaxHp;

//	TCODConsole::root->print(1, sH - 2,  hpDisplayComponent.str());
}