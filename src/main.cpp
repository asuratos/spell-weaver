#include "main.hpp"

Engine engine(80, 50);

int main() {

	while (!TCODConsole::isWindowClosed() && engine.gameState != Engine::LOSE) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	std::cin.get();
}