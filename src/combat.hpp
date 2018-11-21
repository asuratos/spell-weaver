#pragma once

class Combat {
public:
	int atk;

	Combat(int atk);

	void attack(const std::shared_ptr<Entity>& attacker, const std::shared_ptr<Entity>& target);
};