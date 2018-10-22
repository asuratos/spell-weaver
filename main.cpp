#include "main.hpp"
#include <iostream>

Engine engine;

int main() {
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
}