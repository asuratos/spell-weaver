#include "main.hpp"

Ent::Ent(coords loc, int ch, std::string name, const TCODColor &col) : loc(loc), ch(ch), name(name), col(col), blocks(true), combat(nullptr), mortal(nullptr), ai(nullptr) {}

void Ent::update(std::shared_ptr<Ent> owner) { if (ai) ai->update(owner);}

void Ent::render() const {
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col); 
}