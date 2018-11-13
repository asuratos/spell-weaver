#include "main.hpp"

void Ai::update(std::shared_ptr<Entity> owner) {
	if (owner->mortal) {
		if (owner->mortal->isDead()) { return; }
	}
	if (engine.dungeon->isInFov(owner->corporeal->loc.x, owner->corporeal->loc.y)) { moveCount = TRACK_TURNS; }
	else { moveCount++; }
	if (moveCount > 0) { moveOrAttack(owner, engine.player->corporeal->loc.x, engine.player->corporeal->loc.y); }
}

void Ai::moveOrAttack(std::shared_ptr<Entity> owner, int tx, int ty) {
	int dx(tx - owner->corporeal->loc.x), dy(ty - owner->corporeal->loc.y), sdx(dx > 0 ? 1 : -1), sdy(dy > 0 ? 1 : -1), distance((int)sqrt(dx*dx + dy * dy));
	if (distance >= 2) {
		dx = (int)(round(dx / distance)); dy = (int)(round(dy / distance));
		if (engine.dungeon->canWalk(coords(owner->corporeal->loc.x + dx, owner->corporeal->loc.y + dy))) { 
			owner->corporeal->loc.x += dx; owner->corporeal->loc.y += dy; 
		}
		else if (engine.dungeon->canWalk(coords(owner->corporeal->loc.x + sdx, owner->corporeal->loc.y))) { 
			owner->corporeal->loc.x += sdx; 
		}
		else if (engine.dungeon->canWalk(coords(owner->corporeal->loc.x, owner->corporeal->loc.y + sdy))) { 
			owner->corporeal->loc.y += sdy; 
		}
	}
	else if (owner->combat) {
		owner->combat->attack(owner, engine.player);
	}

	owner->clock->decrement(owner->clock->walkCost);
}

void PlayerAi::update(std::shared_ptr<Entity> owner){
	if (owner->mortal) {
		if (owner->mortal->isDead()) {
			return;
		}

		owner->input->process(owner);
	}
}

bool PlayerAi::moveOrAttack(std::shared_ptr<Entity> owner, int tx, int ty) {
	if (engine.dungeon->isWall(tx, ty)) {
	}
	for (auto &ent : engine.entL) {
		if (ent->mortal) {
			if (!ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y==ty) {
			}
		
			else if (ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y == ty) {
				std::cout << "A " << ent->mortal->corpseName << " lies here." << std::endl;
			}
		}
	}
	owner->loc.x = tx;
	owner->loc.y = ty;
	owner->clock->decrement(owner->clock->walkCost);
	return true;
}

static const int TRACK_TURNS(3);

void MobAi::update(std::shared_ptr<Entity> owner) {

}