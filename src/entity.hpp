#pragma once
#include "main.hpp"

struct coords {
	int x, y;

	coords(int x, int y) : x(x), y(y) {}

	coords mod(int dx, int dy);
	coords mod(coords diff);

};


//small components
class Corporeal {
public:
	coords loc;
	bool blocks;

	Corporeal(coords loc, bool blocks); ~Corporeal();
};


//entity class itself only contains pointers to components
class Entity {
public:
	enum entityType {
		ACTOR,
		SPELL
	}entityType;

	int type = ACTOR;
	std::string name;

	//pointers to components go here
	std::shared_ptr<Corporeal> corporeal = nullptr;
	std::shared_ptr<Display> disp = nullptr;
	std::shared_ptr<Clock> clock = nullptr;

	std::shared_ptr<Mortal> mortal = nullptr;
	std::shared_ptr<InputHandler> input = nullptr;
	std::shared_ptr<Combat> combat = nullptr;
	std::shared_ptr<Ai> ai = nullptr;
	/*
	void update(std::shared_ptr<Ent> owner);
	void render() const;
	*/

	Entity(int ch, std::string name, TCODColor &col, int type); ~Entity();
}; 