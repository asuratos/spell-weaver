#include "main.hpp"

void PlayerAi::update(std::shared_ptr<Ent> owner){
	if (owner->mortal) {
		if (owner->mortal->isDead()) {
			return;
		}
		int tx = 0, ty = 0;
		switch (engine.lastKey.vk) {
		case TCODK_CHAR:
			switch (engine.lastKey.c) {
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
			engine.gameState = Engine::TURN;
			if (moveOrAttack(owner, owner->x + tx, owner->y + ty)) { engine.dungeon->computeFov(); }
		}
		
	}
}

bool PlayerAi::moveOrAttack(std::shared_ptr<Ent> owner, int tx, int ty) {
	if (engine.dungeon->isWall(tx, ty)) return false;
	for (auto &ent : engine.entL) {
		if (ent->mortal) {
			if (!ent->mortal->isDead() && ent->x == tx && ent->y==ty) {
				owner->combat->attack(owner, ent); return false;
			}
		}
		else if (ent->mortal->isDead() && ent->x == tx && ent->y == ty) {
			std::cout << "A " << ent->mortal->corpseName << " lies here." << std::endl;
		}
	}
	owner->x = tx;
	owner->y = ty;
	return true;
}

static const int TRACK_TURNS(3);

void MobAi::update(std::shared_ptr<Ent> owner) {
	if (owner->mortal) {
		if (owner->mortal->isDead()) { return; }
	}
	if (engine.dungeon->isInFov(owner->x, owner->y)) { moveCount = TRACK_TURNS; }
	else { moveCount++; }
	if (moveCount > 0) { moveOrAttack(owner, engine.player->x, engine.player->y); }
}

void MobAi::moveOrAttack(std::shared_ptr<Ent> owner, int tx, int ty) {
	int dx(tx - owner->x), dy(ty - owner->y), sdx(dx > 0 ? 1 : -1), sdy(dy > 0 ? 1 : -1), distance((int)sqrt(dx*dx + dy * dy));
	if (distance >= 2) {
		dx = (int)(round(dx / distance)); dy = (int)(round(dy / distance));
		if (engine.dungeon->canWalk(owner->x + dx, owner->y + dy)) { owner->x += dx; owner->y += dy; }
		else if (engine.dungeon->canWalk(owner->x + sdx, owner->y)) { owner->x += sdx; }
		else if (engine.dungeon->canWalk(owner->x, owner->y + sdy)) { owner->y += sdy; }
	}
	else if (owner->combat) { owner->combat->attack(owner, engine.player); }
}