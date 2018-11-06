#pragma once

class Ent {
public:
	int ch, speed; 
	coords loc;
	std::string name;
	bool blocks;

	std::shared_ptr<Combat> combat;
	std::shared_ptr<Ai> ai;
	std::shared_ptr<Mortal> mortal;

	TCODColor col;

	Ent(coords loc, int ch, std::string name, const TCODColor &col);
	

	void update(std::shared_ptr<Ent> owner);
	void render() const;
}; 