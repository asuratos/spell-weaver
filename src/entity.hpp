#pragma once

class Ent {
public:
	int x, y, ch; 
	const std::string name;

	TCODColor col;

	Ent(int x, int y, int ch, const std::string name, const TCODColor &col);
	
	bool moveOrAttack(int x, int y);

	void update();
	void render() const;
};