#pragma once

class InputHandler	 {
public:
	InputHandler(); ~InputHandler();

	void takeTurn(const std::shared_ptr<Entity>& ent);
};