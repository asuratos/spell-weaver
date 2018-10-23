class Ent {
public:
	int x, y, ch; 
	TCODColor col;

	Ent(int x, int y, int ch, const TCODColor &col);
	void render() const;
};