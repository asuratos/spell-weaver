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


};