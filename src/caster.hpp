#pragma once
#include "main.hpp"

class Caster {
	std::string weaves = "";
	int castingCost[5];
	

public:
	enum Element {
		FIRE, EARTH, AIR, WATER, SPIRIT
	};

	Caster(); ~Caster();

	void channel(Element elem, const std::shared_ptr<Entity> &owner);

	std::string getWeaves();

	void release();
};