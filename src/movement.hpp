#pragma once
#include "main.hpp"

class MovementSystem {
public:
	MovementSystem(); ~MovementSystem();

	bool isMoveValid(const std::shared_ptr<Entity>& ent, coords targetloc);
	bool move(const std::shared_ptr<Entity>& ent, coords targetloc);
};