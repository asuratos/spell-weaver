#include "main.hpp"

coords coords::mod(int dx, int dy) {
	return coords(x + dx, y + dy);
}

coords coords::mod(coords diff) {
	return coords(x + diff.x, y + diff.y);
}

Ent::Ent(coords loc, int ch, std::string name, const TCODColor &col) : loc(loc), ch(ch), name(name), col(col), blocks(true) {}

Actor::Actor(coords loc, int ch, std::string name, const TCODColor &col) : Ent(loc, ch, name, col),
	mortal(nullptr),
	clock(nullptr),
	input(nullptr),
	combat(nullptr),
	Pai(nullptr),
	ai(nullptr)	{}

Actor::~Actor() {}

void Actor::update(std::shared_ptr<Actor> owner) { 
	if (ai) ai->update(owner);
	else if (Pai) Pai->update(owner);

}

void Actor::render() const {
	TCODConsole::root->setChar(loc.x, loc.y, ch);
	TCODConsole::root->setCharForeground(loc.x, loc.y, col); 
}

Ent::~Ent(){}
