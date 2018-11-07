#pragma once

class Combat {
public:
	float atk;

	Combat(float atk);

	void attack(std::shared_ptr<Actor> attacker, std::shared_ptr<Actor> target);
};