#pragma once

class Ai {
public:
	int moveCount;

	void update(std::shared_ptr<Entity> owner);
	void moveOrAttack(std::shared_ptr<Entity> owner, int tx, int ty);
};

class PlayerAi : public Ai {
public:
	virtual void update(std::shared_ptr<Entity> owner);
	bool moveOrAttack(std::shared_ptr<Entity> owner,  int tx,  int ty);
};
