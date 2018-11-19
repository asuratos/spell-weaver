#pragma once

class Combat {
public:
	int atk;

	Combat(int atk);

	void attack(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target);
};