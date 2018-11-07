#include "main.hpp"


void PlayerAi::update(std::shared_ptr<Actor> owner){
	if (owner->mortal) {
		if (owner->mortal->isDead()) {
			return;
		}

		owner->input->process(owner);

	}
}

bool PlayerAi::moveOrAttack(std::shared_ptr<Actor> owner, int tx, int ty) {
	if (engine.dungeon->isWall(tx, ty)) {
		owner->clock->decrement(50);
		return false;
	}
	for (auto &ent : engine.entL) {
		std::shared_ptr<Actor> ent = static_cast<std::shared_ptr<Actor>>(ent);
		if (ent->mortal) {
			if (!ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y==ty) {
				owner->combat->attack(owner, ent);
				owner->clock->decrement(50); 
				return false;
			}
		
			else if (ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y == ty) {
				std::cout << "A " << ent->mortal->corpseName << " lies here." << std::endl;
			}
		}
	}
	owner->loc.x = tx;
	owner->loc.y = ty;
	owner->clock->decrement(50);
	return true;
}

static const int TRACK_TURNS(3);

void MobAi::update(std::shared_ptr<Actor> owner) {
	if (owner->mortal) {
		if (owner->mortal->isDead()) { return; }
	}
	if (engine.dungeon->isInFov(owner->loc.x, owner->loc.y)) { moveCount = TRACK_TURNS; }
	else { moveCount++; }
	if (moveCount > 0) { moveOrAttack(owner, engine.player->loc.x, engine.player->loc.y); }
}

void MobAi::moveOrAttack(std::shared_ptr<Actor> owner, int tx, int ty) {
	int dx(tx - owner->loc.x), dy(ty - owner->loc.y), sdx(dx > 0 ? 1 : -1), sdy(dy > 0 ? 1 : -1), distance((int)sqrt(dx*dx + dy * dy));
	if (distance >= 2) {
		dx = (int)(round(dx / distance)); dy = (int)(round(dy / distance));
		if (engine.dungeon->canWalk(coords(owner->loc.x + dx, owner->loc.y + dy))) { owner->loc.x += dx; owner->loc.y += dy; }
		else if (engine.dungeon->canWalk(coords(owner->loc.x + sdx, owner->loc.y))) { owner->loc.x += sdx; }
		else if (engine.dungeon->canWalk(coords(owner->loc.x, owner->loc.y + sdy))) { owner->loc.y += sdy; }
	}
	else if (owner->combat) { 
		std::shared_ptr<Actor> target = static_cast<std::shared_ptr<Actor>>(engine.player);
		owner->combat->attack(owner, target); 
	}

	owner->clock->decrement(50);
}