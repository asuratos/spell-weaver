#pragma once

class InputHandler	 {
public:
	InputHandler(); ~InputHandler();

	void process(std::shared_ptr<Entity> ent);
};