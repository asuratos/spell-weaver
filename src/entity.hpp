#pragma once
#include "main.hpp"

struct coords {
	int x, y;

	coords(int x, int y) : x(x), y(y) {}

	coords operator +(coords a) {
		return coords(a.x + x, a.y + y);
	}

	bool operator ==(coords a) {
		return (a.x == x && a.y == y);
	}
};


//small components
class Spatial {
public:
	coords loc;
	bool blocks;

	Spatial(coords loc, bool blocks); ~Spatial();
};


//entity class itself only contains pointers to components
class Entity {
public:
	enum entityType {
		ACTOR,
		SPELL
	};

	entityType type = ACTOR;
	std::string name;
	bool isPlayer = false;

	//pointers to components go here
	std::shared_ptr<Spatial> spatial = nullptr;
	std::shared_ptr<DisplayComponent> disp = nullptr;
	std::shared_ptr<Clock> clock = nullptr;
	std::shared_ptr<Mortal> mortal = nullptr;
	std::shared_ptr<Combat> combat = nullptr;
	std::shared_ptr<InputHandler> input = nullptr;
	std::shared_ptr<Ai> ai = nullptr;
	std::shared_ptr<Caster> caster = nullptr;
	

	//void update(const std::shared_ptr<Entity>& owner);
	

	Entity(std::string name, entityType type); ~Entity();
}; 