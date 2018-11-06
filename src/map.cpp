#include <iostream>
#include "main.hpp"

static const int rsMin = 6, rsMax = 12;
static const int rMonstersMax = 3;

class bspList : public ITCODBspCallback {
private:
	Map &dungeon; int rNum; int lastx, lasty;
public:
	bspList(Map &dungeon) : dungeon(dungeon), rNum(0) {}
	
	bool visitNode(TCODBsp *node, void *userData) {
		if (node->isLeaf()) {
			int x, y, w, h;
			TCODRandom *rng = TCODRandom::getInstance();
			w = rng->getInt(rsMin, node->w - 2);
			h = rng->getInt(rsMin, node->h - 2);
			x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
			y = rng->getInt(node->y + 1, node->y + node->h - h - 1);

			dungeon.cRoom(rNum == 0, x, y, x + w - 1, y + h - 1);

			if (rNum != 0) {
				dungeon.dig(lastx, lasty, x + w / 2, lasty);
				dungeon.dig(x + w / 2, lasty, x + w / 2, y + h / 2);
			}

			lastx = x + w / 2;
			lasty = y + h / 2;
			rNum++;
		}
		return true;
	}
};


Map::Map(int w, int h) : w(w), h(h) {
	tiles = new Tile[w*h];
	map = std::make_shared<TCODMap>(w, h);

	TCODBsp bsp(0, 0, w, h);
	bsp.splitRecursive(NULL, 8, rsMax, rsMax, 1.5f, 1.5f);
	bspList listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);

	
}


void Map::addMonster(int x, int y) {
	std::random_device seed;
	std::default_random_engine dRoll(seed());
	std::uniform_int_distribution<int> d100(1, 100);

	auto dice = std::bind(d100, dRoll);

	int mDice(dice());
	if (mDice < 80) {
		std::shared_ptr<Ent> gromlin = std::make_shared<Ent>(x, y, 'g', "Gromlin", TCODColor::desaturatedGreen);
		gromlin->mortal = std::make_shared<npcMortal>(10, 0, "dead gromlin");
		gromlin->combat = std::make_shared<Combat>(3);
		gromlin->ai = std::make_shared<MobAi>();
		engine.entL.push_back(gromlin);
	}
	else {
		std::shared_ptr<Ent> hobgobbo = std::make_shared<Ent>(x, y, 'h', "Hobgobbo", TCODColor::darkOrange);
		hobgobbo->mortal = std::make_shared<npcMortal>(16, 1, "dead hobgobbo");
		hobgobbo->combat = std::make_shared<Combat>(4);
		hobgobbo->ai = std::make_shared<MobAi>();
		engine.entL.push_back(hobgobbo);
	}

}

void Map::dig(int x1, int y1, int x2, int y2) {
	if (x2 < x1) { int tmp = x2; x2 = x1, x1 = tmp; }
	if (y2 < y1) { int tmp = y2; y2 = y1; y1 = tmp; }

	for (int tx = x1; tx <= x2; tx++) {
		for (int ty = y1; ty <= y2; ty++) {
			map->setProperties(tx, ty, true, true);
		}
	}
}

void Map::cRoom(bool first, int x1, int y1, int x2, int y2) {
	dig(x1, y1, x2, y2);
	int cx((x1 + x2) / 2), cy = ((y1 + y2) / 2);
	if (first) {
		engine.player->loc.x = cx;
		engine.player->loc.y = cy;
	}
	else {
		TCODRandom *rng = TCODRandom::getInstance();
		int nbMonsters(rng->getInt(0, rMonstersMax));
		while (nbMonsters > 0) {
			int x(rng->getInt(x1, x2)), y(rng->getInt(y1, y2));
			if (canWalk(x, y)) { addMonster(x, y); }
			nbMonsters--;
		}
		//if (rng->getInt(0, 3) == 0) { engine.entL.emplace_back(std::make_shared<Ent>(cx, cy, '@', "NPC", TCODColor::yellow)); }
	}
}


Map::~Map() { delete [] tiles; }

bool Map::isWall(int x, int y) const { return !map->isWalkable(x,y); }

bool Map::isExplored(int x, int y) const { return tiles[x + y * w].explored; }

bool Map::isInFov(int x, int y) const {
	if (map->isInFov(x, y)) { tiles[x + y * w].explored = true; return true; }
	return false;
}

void Map::computeFov() {
	map->computeFov(engine.player->loc.x, engine.player->loc.y, engine.fovRad);
}

bool Map::canWalk(int x, int y) const {
	if (isWall(x, y)) { return false; }
	for (auto &ent : engine.entL) { if (ent->loc.x == x && ent->loc.y == y) { return false; } }
	return true;
}

void Map::render() const {
	static const TCODColor dWall(0, 0, 30), 
		dFloor(50, 50, 80),
		lWall(80, 80, 110),
		lFloor(100, 100, 100);


	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			if (isInFov(x, y)) {
				TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? lWall : lFloor);
				TCODConsole::root->putChar(x, y, isWall(x, y) ? '#' : '.');
			}
			else if (isExplored(x, y)) {
				TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? dWall : dFloor);
			}
		}
	}
}