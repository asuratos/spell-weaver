#pragma once

//the display component for entities that appear on the screen. contains redering information.

class DisplayComponent {
public:
	int ch;
	TCODColor col;

	DisplayComponent(int ch, const TCODColor &col);
	~DisplayComponent();

	void render(const std::shared_ptr<Entity> &owner);
};