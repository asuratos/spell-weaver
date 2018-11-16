#include "main.hpp"

MovementSystem::MovementSystem() {}

MovementSystem::~MovementSystem() {}

bool MovementSystem::isMoveValid(std::shared_ptr<Entity> ent, coords targetloc) {

}

bool MovementSystem::move(std::shared_ptr<Entity> owner, coords targetloc) {
	if (engine.dungeon->isWall(targetloc.x, targetloc.y)) {
		owner->clock->decrement(owner->clock->walkCost);
		return false;
	}

	for (auto &ent : engine.entL) {
		if (ent->spatial && ent->spatial->loc == targetloc) {
			if (!ent->spatial->blocks) {
				if (ent->mortal){
					if (!ent->mortal->isDead()) {
						owner->combat->attack(owner, ent);
						owner->clock->decrement(owner->clock->walkCost);
						return false;
					}
				}
				else {
					owner->clock->decrement(owner->clock->walkCost);
					return true;
				}
			}
		}
	}

	owner->spatial->loc = targetloc;
	owner->clock->decrement(owner->clock->walkCost);
	return true;
}