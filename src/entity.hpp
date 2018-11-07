#pragma once

struct coords {
	int x, y;

	coords(int x, int y) : x(x), y(y) {}
};

class Ent {
public:
	int ch, speed, energy; 
	coords loc;
	std::string name;
	bool blocks;

	std::shared_ptr<InputHandler> input;
	std::shared_ptr<Combat> combat;
	std::shared_ptr<PlayerAi> Pai;
	std::shared_ptr<Ai> ai;
	std::shared_ptr<Mortal> mortal;

	TCODColor col;

	Ent(coords loc, int ch, std::string name, const TCODColor &col);
	

	void update(std::shared_ptr<Ent> owner);
	void render() const;
}; 