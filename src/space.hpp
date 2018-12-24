#pragma once

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