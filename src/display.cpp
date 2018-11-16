#include "main.hpp"

Display::Display(int ch, TCODColor col) : ch(ch), col(col) {}

Display::~Display() {}

void Display::render(std::shared_ptr<Entity> owner) {
	switch (owner->type) {
	case Entity::ACTOR:
		TCODConsole::root->setChar(owner->corporeal->loc.x, owner->corporeal->loc.y, ch);
		TCODConsole::root->setCharForeground(owner->corporeal->loc.x, owner->corporeal->loc.y, col);
		break;
	case Entity::SPELL:
		//spell rendering not yet implemented, as spells are not yet implemented
		break;
	}
}