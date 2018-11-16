#include "main.hpp"

DisplayComponent::DisplayComponent(int ch, TCODColor col) : ch(ch), col(col) {}

DisplayComponent::~DisplayComponent() {}

void DisplayComponent::render(std::shared_ptr<Entity> owner) {
	switch (owner->type) {
	case Entity::ACTOR:
		TCODConsole::root->setChar(owner->spatial->loc.x, owner->spatial->loc.y, ch);
		TCODConsole::root->setCharForeground(owner->spatial->loc.x, owner->spatial->loc.y, col);
		break;
	case Entity::SPELL:
		//spell rendering not yet implemented, as spells are not yet implemented
		break;
	}
}