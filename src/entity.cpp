#include "main.hpp"

Ent::Ent(int x, int y, int ch, const std::string name, const TCODColor &col) : x(x), y(y), ch(ch), name(name), col(col) {}

bool Ent::moveOrAttack(int x, int y) {
	if (engine.dungeon->isWall(x, y)) { return false; }
	for (auto &ent : engine.entL) {
		if (ent->x == x && ent->y == y) {
			std::cout << "The " << ent->name << " avoids your attack!" << std::endl;
			return false;
		}
	}
	this->x = x;
	this->y = y;
	return true;
}

void Ent::update() {
	if (engine.dungeon->isInFov(this->x, this->y)) {
		std::cout << "The " << name << " grunts" << std::endl;
	}
}

void Ent::render() const {
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col); 
}