#include "main.hpp"	

Gui::Gui(int height) : h(height) {
	con = new TCODConsole(engine.sW, h);
}

Gui::~Gui() { delete con;  log.clear(); }

void Gui::render() {
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	//draw boxes
	con->setDefaultForeground(TCODColor::white);
	con->printFrame(0, 0, 14, h);
	con->printFrame(14, 0, engine.sW - 14, h);

	//HP Bar
	renderBar(1, 1, 12, "HP", (float)engine.player->mortal->hp, (float)engine.player->mortal->MaxHp, TCODColor::darkerRed, TCODColor::lightRed);

	//spell cache
	con->print(1, 2, std::string("[ ][ ][ ]"));

	//render messages in log
	int lineno = 1; float opac = 1.0f;
	for (std::vector<std::shared_ptr<Gui::Message>>::reverse_iterator i = log.rbegin(); i != log.rend() ; i++) {
		con->setDefaultForeground((*i)->col * opac);
		con->TCODConsole::print(15, lineno, (*i)->message);		
		if (lineno == h - 2) {
			break;
		}
		lineno++;
		opac = opac * 0.9f;
	}

	TCODConsole::blit(con, 0, 0, engine.sW, h, TCODConsole::root, 0, engine.sH - h);
}

void Gui::renderBar(int x, int y, int width, std::string label, float val, float maxVal, const TCODColor &back, const TCODColor &fore) {
	//render HP bar (Encapsulate this later)
//first print the rectangle
	con->setDefaultBackground(back);
	con->rect(x, y, width, 1, false, TCOD_BKGND_SET);

	int barwidth = (int)(val / maxVal * width);
	if (barwidth > 0) {
		con->setDefaultBackground(fore);
		con->rect(x, y, barwidth, 1, false, TCOD_BKGND_SET);
	}

	//next, display HP amount
	con->setDefaultForeground(TCODColor::white);
	con->print(x + width / 2, y,
		"HP : " + std::to_string((int)val) + "/" + std::to_string((int)maxVal),
		TCOD_CENTER, TCOD_BKGND_NONE);
}

void Gui::message(std::string message, const TCODColor &col) {
	log.emplace_back(std::make_shared<Message>(message, col));
	if (log.size() == 30) {
		log.erase(log.begin());
	}
}

Gui::Message::Message(std::string message, const TCODColor &col) : message(message), col(col) {}

Gui::Message::~Message() {}