#include "main.hpp"


Fire::Fire(int x, int y) : x(x), y(y) {}

Element* FireFactory::create(int x, int y) { return new Fire(x, y); }

LineSpell::LineSpell(std::shared_ptr<Element> spellElement, const int originx, const int originy, const int range, const int direct) :
spellElement(spellElement), originx(originx), originy(originy), range(range), direct(direct) {}

void LineSpell::update(int range, int direct){
	
	int dx = 0, dy = 0;



	switch (direct) {
	case UP: dy = -1; break;
	case LEFT: dx = -1; break;
	case RIGHT: dx = 1; break;
	case DOWN: dy = 1; break;
	}

	for (int i=0; i <= range; i++) {
		//create fire
		engine.magicL.emplace_back(new Element(originx + i * dx, originy + i * dy));
	}
}