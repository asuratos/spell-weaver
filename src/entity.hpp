#pragma once

class Ent {
public:
	int x, y, ch; 
	std::string name;
	bool blocks;

	std::shared_ptr<Combat> combat;
	std::shared_ptr<Ai> ai;
	std::shared_ptr<Mortal> mortal;

	TCODColor col;

	Ent(int x, int y, int ch, const std::string name, const TCODColor &col);
	

	void update(std::shared_ptr<Ent> owner);
	void render() const;
}; //