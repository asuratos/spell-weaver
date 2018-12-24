#include "main.hpp"


Entity::Entity(std::string name, entityType type) : name(name), type(type) {}

Entity::~Entity() {}

/*
void Entity::update(const std::shared_ptr<Entity>& owner) { 
	if (ai) ai->update(owner);
}

void Actor::render() const {
	TCODConsole::root->setChar(loc.x, loc.y, ch);
	TCODConsole::root->setCharForeground(loc.x, loc.y, col); 
}
*/
