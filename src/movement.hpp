#pragma once
#include "main.hpp"

class MovementSystem {
public:
	MovementSystem(); ~MovementSystem();

	bool isMoveValid(std::shared_ptr<Entity> ent, coords targetloc);
	bool move(std::shared_ptr<Entity> ent, coords targetloc);
};