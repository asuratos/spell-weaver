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

	virtual void update(const std::shared_ptr<ElementUnit> self) = 0;
};

class FireElement : public ElementUnit {
protected:
	TCODColor color = TCODColor::white;
	

public:
	FireElement(coords loc);

	void update(const std::shared_ptr<ElementUnit> self);
};