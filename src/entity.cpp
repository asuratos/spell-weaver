#include "main.hpp"

Ent::Ent(int x, int y, int ch, const TCODColor &col) : x(x), y(y), ch(ch), col(col) {}

void Ent::render() const {
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col); //testing push from lab pc
}