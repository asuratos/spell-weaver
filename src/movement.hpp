#pragma once
#include "main.hpp"

class MovementSystem {
public:
	MovementSystem(); ~MovementSystem();

	bool move(std::shared_ptr<Entity>, coords targetloc);
};