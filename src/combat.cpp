#include "main.hpp"

Combat::Combat(int atk) : atk(atk) {};

void Combat::attack(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target) {
	if (target->mortal) {
		if (!target->mortal->isDead()) {
			int dmg = atk - target->mortal->def;
			if (dmg > 0.0) {
				engine.gui->message(
					attacker->name + " attacks " + target->name + " for " + std::to_string(dmg) + " damage!",
					attacker->isPlayer ? TCODColor::white : TCODColor::red
				);
				//std::cout << attacker->name << " attacks " << target->name << " for " << dmg << " damage!" << std::endl;

				target->mortal->takeDamage(target, atk);
			}	
		}
	}
}