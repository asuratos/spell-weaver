#include "main.hpp"

coords coords::mod(int dx, int dy) {
	return coords(x + dx, y + dy);
}

coords coords::mod(coords diff) {
	return coords(x + diff.x, y + diff.y);
}

Corporeal::Corporeal(coords loc, bool blocks) : loc(loc), blocks(blocks) {}

Corporeal::~Corporeal() {}

Entity::Entity(int ch, std::string name, TCODColor &col, int type) : ch(ch), name(name), col(col), type(type) {}

Entity::~Entity() {}

/*
void Actor::update(std::shared_ptr<Actor> owner) { 
	if (ai) ai->update(owner);
	else if (Pai) Pai->update(owner);

}

void Actor::render() const {
	TCODConsole::root->setChar(loc.x, loc.y, ch);
	TCODConsole::root->setCharForeground(loc.x, loc.y, col); 
}
*/
