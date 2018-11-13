#pragma once

class Mortal {
public:
	float MaxHp, hp, def;
	const std::string corpseName;

	Mortal(float MaxHp, float def, std::string corpseName);

	bool isDead() { return hp <= 0; }

	float takeDamage(std::shared_ptr<Entity> owner, float dmg);

	void die(std::shared_ptr<Entity> owner);
};