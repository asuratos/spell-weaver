#pragma once
#include "main.hpp"


class Gui {
public:
	int w, h;

	Gui(int height); ~Gui();

	void render();
	void message(std::string message, const TCODColor &col);

protected:
	TCODConsole * con; 

	struct Message {
		std::string message;
		TCODColor col;

		Message(std::string message, const TCODColor &col);
		~Message();
	};

	std::vector<std::shared_ptr<Message>> log;

	void renderBar(int x, int y, int w, std::string label,
		float val, float maxVal,
		const TCODColor &back,
		const TCODColor &fore);

	void renderBar(int x, int y, int w, std::string label,
		const TCODColor &back,
		const TCODColor &fore);


};