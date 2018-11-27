#pragma once

class SpellComponent {
protected:
	std::map<coords, coords> spellfront;
	std::shared_ptr<ElementFactory> elementfactory;

public:
	SpellComponent(std::map<coords, coords> front);

	virtual ~SpellComponent();

	void createElement();

	virtual void update() = 0;
};

class LineSpell : public SpellComponent {

	void update();
};