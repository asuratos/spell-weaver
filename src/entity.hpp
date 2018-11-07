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

	TCODColor col;

	virtual void update() = 0;
	virtual void render() = 0;

	virtual ~Ent();

protected:
	Ent(coords loc, int ch, std::string name, const TCODColor &col) : loc(loc), ch(ch), name(name), col(col), blocks(true){}
}; 

class Actor : public Ent {
public:
	std::shared_ptr<Mortal> mortal = {};
	std::shared_ptr<Clock> clock = {};
	std::shared_ptr<InputHandler> input = {};
	std::shared_ptr<Combat> combat = {};
	std::shared_ptr<PlayerAi> Pai = {};
	std::shared_ptr<Ai> ai = {};

	Actor(coords loc, int ch, std::string name, const TCODColor &col) : Ent(loc, ch, name, col) {}; ~Actor();

	void update(std::shared_ptr<Actor> owner);
	void render() const;
};