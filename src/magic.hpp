#pragma once

class Element {
public:
	virtual void update() = 0;
	virtual void damage() = 0;
	virtual void render() const;
};


class Fire : public Element{
public:
	Fire(int x, int y);	~Fire();

	void damage();

	void update(int dur);
	void render() const;

private:
	int x, y;
	int dur = 3;
};

class ElementFactory {
public:
	Element* create(int x, int y) = 0;
};

class FireFactory :public ElementFactory {
public:
	Element* create(int x, int y);
};

class SpellShape {
public:
	enum direction {
		UP,
		LEFT,
		RIGHT,
		DOWN
	}direction;

	virtual void update();
};

class LineSpell : public SpellShape{
public:
	LineSpell(std::shared_ptr<Element> spellElement, const int originx, const int originy, const int range, const int direct); ~LineSpell();

	void update(int range, int direct);

private:
	int range;
	const int direct, originx, originy;

	std::shared_ptr<Element> spellElement;

};