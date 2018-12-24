#include "main.hpp"

MagicSystem::MagicSystem() {}

MagicSystem::~MagicSystem() {}

MagicSystem::spellName MagicSystem::lookup(std::string spellstring) {
	std::map<std::string, Spell> spellList = {};
}

void MagicSystem::castSpell(const std::shared_ptr<Entity> &ent) {
	//first get the spell
	std::string spellstring = ent->caster->getWeaves();

	//figure out what spell to cast
	std::sort(spellstring.begin(), spellstring.end());

	//AEFSW
	//spellName spell = lookup(spellstring);
	engine.gui->message(spellstring, TCODColor::white);

	//switch (spell) {
	//case WHATEVER: engine.gui->message(spellstring, TCODColor::red); break;
	//}

	//if it requires a direction, ask for direction
	//create Spell moving in that direction
	//clear cache
	ent->caster->release();

	//decrement clock
	ent->clock->decrement(50);
}