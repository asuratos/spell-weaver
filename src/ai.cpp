#include "main.hpp"

Ai::~Ai() {}

PlayerAi::PlayerAi() {}

PlayerAi::~PlayerAi() {}

void PlayerAi::update(std::shared_ptr<Entity> owner){
	if (owner->mortal) {
		if (owner->mortal->isDead()) {
			return;
		}


		owner->input->process(owner);
	}
}

bool PlayerAi::tryToMove(std::shared_ptr<Entity> owner, int tx, int ty) {
	if (engine.dungeon->isWall(tx, ty)) {
		owner->clock->decrement(owner->clock->walkCost);
		return false;
	}
	for (auto &ent : engine.entL) {
		if (ent->mortal) {
			if (!ent->mortal->isDead() && (ent->ai->faction != owner->ai->faction)  && ent->spatial->loc.x == tx && ent->spatial->loc.y==ty) {
				//attack the thing
				owner->combat->attack(owner, ent);
			}
		
			else if (ent->mortal->isDead() && ent->spatial->loc.x == tx && ent->spatial->loc.y == ty) {
				std::cout << "A " << ent->mortal->corpseName << " lies here." << std::endl;
			}
		}
	}
	owner->spatial->loc.x = tx;
	owner->spatial->loc.y = ty;
	owner->clock->decrement(owner->clock->walkCost);
	return true;
}

static const int TRACK_TURNS(3);

MeleeAi::MeleeAi(Ai::Mode mode) {}

void MeleeAi::update(std::shared_ptr<Entity> owner) {
	//mob decision making here
	if (owner->mortal) {
		if (owner->mortal->isDead()) { return; }
	}
	if (engine.dungeon->isInFov(owner->spatial->loc.x, owner->spatial->loc.y)) { moveCount = TRACK_TURNS; }
	else { moveCount++; }
	if (moveCount > 0) { tryToMove(owner, engine.player->spatial->loc.x, engine.player->spatial->loc.y); }
}

bool MeleeAi::tryToMove(std::shared_ptr<Entity> owner, int tx, int ty) {
	//mob pathing should be here
	int dx(tx - owner->spatial->loc.x), dy(ty - owner->spatial->loc.y), sdx(dx > 0 ? 1 : -1), sdy(dy > 0 ? 1 : -1), distance((int)sqrt(dx*dx + dy * dy));
	if (distance >= 2) {
		dx = (int)(round(dx / distance)); dy = (int)(round(dy / distance));
		if (engine.dungeon->canWalk(coords(owner->spatial->loc.x + dx, owner->spatial->loc.y + dy))) {
			owner->spatial->loc.x += dx; owner->spatial->loc.y += dy;
		}
		else if (engine.dungeon->canWalk(coords(owner->spatial->loc.x + sdx, owner->spatial->loc.y))) {
			owner->spatial->loc.x += sdx;
		}
		else if (engine.dungeon->canWalk(coords(owner->spatial->loc.x, owner->spatial->loc.y + sdy))) {
			owner->spatial->loc.y += sdy;
		}
		return true;
	}
	else if (owner->combat) {
		owner->combat->attack(owner, engine.player);
		return false;
	}

	owner->clock->decrement(owner->clock->walkCost);
	return true;
}