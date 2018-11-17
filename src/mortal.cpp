#include "main.hpp"

Mortal::Mortal(int MaxHp, int def, const std::string corpseName) : MaxHp(MaxHp), def(def), corpseName(corpseName), hp(MaxHp) {};

int Mortal::takeDamage(std::shared_ptr<Entity> owner, int dmg) {
	dmg -= def;
	if (dmg > 0) { hp -= dmg; if (hp <= 0) { die(owner); } }
	else { dmg = 0; }
	return dmg;
}

void Mortal::die(std::shared_ptr<Entity> owner) {
	if (owner->isPlayer) {
		std::cout << "You have been slain..." << std::endl;
		engine.gameState = Engine::LOSE;
	}
	else {
		std::cout << "The " << owner->name << " has been slain." << std::endl;
	}

	owner->disp->ch = '%';
	owner->disp->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->spatial->blocks = false;
	owner->clock = nullptr;

}
