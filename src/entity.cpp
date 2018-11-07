#include "main.hpp"

Ent::Ent(coords loc, int ch, std::string name, const TCODColor &col) : loc(loc), ch(ch), name(name), col(col), blocks(true), 
input(nullptr), combat(nullptr), mortal(nullptr), ai(nullptr), Pai(nullptr) {}

void Ent::update(std::shared_ptr<Ent> owner) { 
	if (ai) ai->update(owner);
	else if (Pai) Pai->update(owner);

}

void Ent::render() const {
	TCODConsole::root->setChar(loc.x, loc.y, ch);
	TCODConsole::root->setCharForeground(loc.x, loc.y, col); 
}