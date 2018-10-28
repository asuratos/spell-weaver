#include "main.hpp"

Mortal::Mortal(float MaxHp, float def, const std::string corpseName) : MaxHp(MaxHp), def(def), corpseName(corpseName), hp(MaxHp) {};

float Mortal::takeDamage(std::shared_ptr<Ent> owner, float dmg) {
	dmg -= def;
	if (dmg > 0) { hp -= dmg; if (hp <= 0) { die(owner); } }
	else { dmg = 0; }
	return dmg;
}

void Mortal::die(std::shared_ptr<Ent> owner) {
	owner->ch = '%';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;
}

pcMortal::pcMortal(float MaxHp, float def, std::string corpseName) :
	Mortal(MaxHp, def, corpseName) {}

npcMortal::npcMortal(float MaxHp, float def, std::string corpseName) :
	Mortal(MaxHp, def, corpseName) {}

void pcMortal::die(std::shared_ptr<Ent> owner) {
	std::cout << "You have been slain..." << std::endl;
	Mortal::die(owner);
	engine.gameState = Engine::LOSE;
}

void npcMortal::die(std::shared_ptr<Ent> owner) {
	std::cout << "The " << owner->name << " has been slain." << std::endl;
	Mortal::die(owner);
}