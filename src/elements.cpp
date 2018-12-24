#include "main.hpp"

ElementUnit::ElementUnit(coords loc) : loc(loc) {}

ElementUnit::~ElementUnit() {}


FireElement::FireElement(coords loc) : ElementUnit(loc) {}

void FireElement::update(std::shared_ptr<ElementUnit> self) {};