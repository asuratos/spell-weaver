#pragma once

struct Tile {
	bool explored; 
	Tile() : explored (false) {}
};

class Map {
public:
	int w, h;

	Map(int w, int h); ~Map();


	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;
	bool isWall(int x, int y) const;
	bool canWalk(int x, int y) const;
	
	void addMonster(int x, int y);
	void computeFov();
	void render() const;

protected:
	Tile * tiles;
	friend class bspList;

	std::shared_ptr<TCODMap> map;

	void dig(int x1, int y1, int x2, int y2),
		cRoom(bool first, int x1, int y1, int x2, int y2),
		setWall(int x, int y);
};