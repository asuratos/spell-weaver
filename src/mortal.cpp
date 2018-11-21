#include "main.hpp"

Mortal::Mortal(int MaxHp, int def, const std::string corpseName) : MaxHp(MaxHp), def(def), corpseName(corpseName), hp(MaxHp) {};

int Mortal::takeDamage(const std::shared_ptr<Entity>& owner, int dmg) {
	dmg -= def;
	if (dmg > 0) { hp -= dmg; if (hp <= 0) { die(owner); } }
	else { dmg = 0; }
	return dmg;
}

void Mortal::die(const std::shared_ptr<Entity>& owner) {
	if (owner->isPlayer) {
		engine.gui->message("You have been slain...", TCODColor::darkRed);
		//std::cout << "You have been slain..." << std::endl;
		engine.gameState = Engine::LOSE;
	}
	else {
		engine.gui->message(
			"The " + owner->name + "has been slain.",
			TCODColor::lightBlue
		);
		//std::cout << "The " << owner->name << " has been slain." << std::endl;
	}

	owner->disp->ch = '%';
	owner->disp->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->spatial->blocks = false;
	owner->clock = nullptr;

}
