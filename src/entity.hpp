#pragma once

struct coords {
	int x, y;

	coords(int x, int y) : x(x), y(y) {}

	coords mod(int dx, int dy);
	coords mod(coords diff);

};

class Ent {
public:
	int ch; 
	coords loc;
	std::string name;
	bool blocks;

	std::shared_ptr<InputHandler> input;
	std::shared_ptr<Combat> combat;
	std::shared_ptr<PlayerAi> Pai;
	std::shared_ptr<Ai> ai;
	std::shared_ptr<Mortal> mortal;
	std::shared_ptr<Clock> clock;

	TCODColor col;

	Ent(coords loc, int ch, std::string name, const TCODColor &col);
	

	void update(std::shared_ptr<Ent> owner);
	void render() const;
}; 

