#include "main.hpp"

Mortal::Mortal(float MaxHp, float def, const std::string corpseName) : MaxHp(MaxHp), def(def), corpseName(corpseName), hp(MaxHp) {};

float Mortal::takeDamage(std::shared_ptr<Entity> owner, float dmg) {
	dmg -= def;
	if (dmg > 0) { hp -= dmg; if (hp <= 0) { die(owner); } }
	else { dmg = 0; }
	return dmg;
}

void Mortal::die(std::shared_ptr<Entity> owner) {
	owner->disp->ch = '%';
	owner->disp->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->corporeal->blocks = false;
	owner->clock = nullptr;

	if (owner->isPlayer) {
		std::cout << "You have been slain..." << std::endl;
		Mortal::die(owner);
		engine.gameState = Engine::LOSE;
	}
	else {
		std::cout << "The " << owner->name << " has been slain." << std::endl;
	}
}
