#pragma once

class Mortal {
public:
	int MaxHp, hp, def;
	const std::string corpseName;

	Mortal(int MaxHp, int def, std::string corpseName);

	bool isDead() { return hp <= 0; }

	int takeDamage(std::shared_ptr<Entity> owner, int dmg);

	void die(std::shared_ptr<Entity> owner);
};