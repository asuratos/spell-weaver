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
			if (moveOrAttack(owner, owner->loc.x + tx, owner->loc.y + ty)) { engine.dungeon->computeFov(); }
		}
		
	}
}

bool PlayerAi::moveOrAttack(std::shared_ptr<Ent> owner, int tx, int ty) {
	if (engine.dungeon->isWall(tx, ty)) return false;
	for (auto &ent : engine.entL) {
		if (ent->mortal) {
			if (!ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y==ty) {
				owner->combat->attack(owner, ent); return false;
			}
		}
		else if (ent->mortal->isDead() && ent->loc.x == tx && ent->loc.y == ty) {
			std::cout << "A " << ent->mortal->corpseName << " lies here." << std::endl;
		}
	}
	owner->loc.x = tx;
	owner->loc.y = ty;
	return true;
}

static const int TRACK_TURNS(3);

void MobAi::update(std::shared_ptr<Ent> owner) {
	if (owner->mortal) {
		if (owner->mortal->isDead()) { return; }
	}
	if (engine.dungeon->isInFov(owner->loc.x, owner->loc.y)) { moveCount = TRACK_TURNS; }
	else { moveCount++; }
	if (moveCount > 0) { moveOrAttack(owner, engine.player->loc.x, engine.player->loc.y); }
}

void MobAi::moveOrAttack(std::shared_ptr<Ent> owner, int tx, int ty) {
	int dx(tx - owner->loc.x), dy(ty - owner->loc.y), sdx(dx > 0 ? 1 : -1), sdy(dy > 0 ? 1 : -1), distance((int)sqrt(dx*dx + dy * dy));
	if (distance >= 2) {
		dx = (int)(round(dx / distance)); dy = (int)(round(dy / distance));
		if (engine.dungeon->canWalk(owner->loc.x + dx, owner->loc.y + dy)) { owner->loc.x += dx; owner->loc.y += dy; }
		else if (engine.dungeon->canWalk(owner->loc.x + sdx, owner->loc.y)) { owner->loc.x += sdx; }
		else if (engine.dungeon->canWalk(owner->loc.x, owner->loc.y + sdy)) { owner->loc.y += sdy; }
	}
	else if (owner->combat) { owner->combat->attack(owner, engine.player); }
}