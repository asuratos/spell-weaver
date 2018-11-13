#include "main.hpp"

Corporeal::Corporeal(coords loc, bool blocks) : loc(loc), blocks(blocks) {}

Corporeal::~Corporeal() {}

Entity::Entity(std::string name, entityType type) : name(name), type(type) {}

Entity::~Entity() {}


void Entity::update(std::shared_ptr<Entity> owner) { 
	if (ai) ai->update(owner);
	else if (input) input->process(owner);
}
/*
void Actor::render() const {
	TCODConsole::root->setChar(loc.x, loc.y, ch);
	TCODConsole::root->setCharForeground(loc.x, loc.y, col); 
}
*/
