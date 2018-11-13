#pragma once

//the display component for entities that appear on the screen. contains redering information.

class Display {
public:
	int ch;
	TCODColor col;

	Display(int ch, TCODColor &col); ~Display();

	void render(std::shared_ptr<Entity> owner);
};