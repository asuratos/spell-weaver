#pragma once

class ElementFactory{};

class ElementUnit {
protected:
	coords loc;
	int lifetime;
	bool expired = false;

public:
	ElementUnit(coords loc);

	virtual ~ElementUnit();

	virtual void update(const std::shared_ptr<ElementUnit> self);
};

class FireElement : public ElementUnit {
protected:
	TCODColor color = TCODColor::white;
	

public:
	FireElement(coords loc) : ElementUnit(loc);

	void update(const std::shared_ptr<ElementUnit> self);
};