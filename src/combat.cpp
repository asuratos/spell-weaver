#include "main.hpp"

Combat::Combat(float atk) : atk(atk) {};

void Combat::attack(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target) {
	if (target->mortal) {
		if (!target->mortal->isDead()) {
			float dmg = atk - target->mortal->def;
			if (dmg > 0.0) {
				std::cout << attacker->name << " attacks " << target->name << " for " << dmg << " damage!" << std::endl;

				target->mortal->takeDamage(target, atk);
			}	
		}
	}
}