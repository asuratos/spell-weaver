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
	con->printFrame(0, 0, 15, h);
	con->printFrame(15, 0, engine.sW - 15, h);

	//render HP bar
	Gui::Message msg = Gui::Message(std::string("blah"), TCODColor::black);
	msg.col;
	//render messages in log
	
	int lineno = 1; float opac = 1.0f;
	for (std::vector<std::shared_ptr<Gui::Message>>::reverse_iterator i = log.rbegin(); i != log.rend() ; i++) {
		con->setDefaultForeground((*i)->col * opac);
		con->TCODConsole::printf(16, lineno, (*i)->message.c_str());		
		if (lineno == h - 2) {
			break;
		}
		lineno++;
		opac = opac * 0.9f;
	}

	TCODConsole::blit(con, 0, 0, engine.sW, h, TCODConsole::root, 0, engine.sH - h);
}

void Gui::message(std::string message, const TCODColor &col) {
	log.emplace_back(std::make_shared<Message>(message, col));
	if (log.size() == 30) {
		log.erase(log.begin());
	}
}

Gui::Message::Message(std::string message, const TCODColor &col) : message(message), col(col) {}

Gui::Message::~Message() {}