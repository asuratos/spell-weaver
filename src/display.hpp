#pragma once

//the display component for entities that appear on the screen. contains redering information.

class DisplayComponent {
public:
	int ch;
	TCODColor col;

	DisplayComponent(int ch, TCODColor col);
	~DisplayComponent();

	void render(std::shared_ptr<Entity> owner);
};