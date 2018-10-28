#pragma once

class Mortal {
public:
	float MaxHp, hp, def;
	const std::string corpseName;

	Mortal(float MaxHp, float def, std::string corpseName);

	bool isDead() { return hp <= 0; }

	float takeDamage(std::shared_ptr<Ent> owner, float dmg);

	virtual void die(std::shared_ptr<Ent> owner) = 0;
};

class pcMortal : public Mortal {
public:
	pcMortal(float MaxHp, float def, const std::string corpseName);

	void die(std::shared_ptr<Ent> owner);
};

class npcMortal : public Mortal {
public:
	npcMortal(float MaxHp, float def, const std::string corpseName);

	void die(std::shared_ptr<Ent> owner);
};