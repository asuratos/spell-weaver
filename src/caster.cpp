#include "main.hpp"

Caster::Caster() : castingCost{ 50, 50, 50, 50, 50 } {}

Caster::~Caster() {}

void Caster::channel(Caster::Element elem, std::shared_ptr<Entity> owner) {
	if (weaves.size() >= 3) {
		engine.gui->message("You cannot hold any more of the One Power!", TCODColor::lightRed);
		return;
	}

	std::string new_weave = "";

	switch (elem) {
	case FIRE:
		new_weave = "F"; 
		owner->clock->decrement(castingCost[FIRE]);
		if (owner->isPlayer) {
			engine.gui->message("You channel a weave of Fire!", TCODColor::lightRed);
		}
		break;
	case EARTH:
		new_weave = "E";
		owner->clock->decrement(castingCost[EARTH]);
		if (owner->isPlayer) {
			engine.gui->message("You channel a weave of Earth!", TCODColor::lightAmber);
		}
		break;
	case AIR:
		new_weave = "A";
		owner->clock->decrement(castingCost[AIR]);
		if (owner->isPlayer) {
			engine.gui->message("You channel a weave of Air!", TCODColor::lightGreen);
		}
		break;
	case WATER:
		new_weave = "W";
		owner->clock->decrement(castingCost[WATER]);

		if (owner->isPlayer) {
			engine.gui->message("You channel a weave of Water!", TCODColor::lightBlue);
		}
		break;
	case SPIRIT:
		new_weave = "S"; 
		owner->clock->decrement(castingCost[SPIRIT]);
		if (owner->isPlayer) {
			engine.gui->message("You channel a weave of Spirit!", TCODColor::cyan);
		}
		break;
	}

	weaves = weaves + new_weave;
}

void Caster::release(std::shared_ptr<Entity> owner) {
	weaves.clear();
	if (owner->isPlayer) {
		engine.gui->message("You release the One Power.", TCODColor::white);
	}
}


std::string Caster::getWeaves() {
	return weaves;
}