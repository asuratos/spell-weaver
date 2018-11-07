#pragma once

class Ai {
public:
	virtual void update(std::shared_ptr<Actor> owner) = 0;
};

class PlayerAi : public Ai {
public:
	virtual void update(std::shared_ptr<Actor> owner);
	bool moveOrAttack(std::shared_ptr<Actor> owner,  int tx,  int ty);
};

class MobAi : public Ai {
public:
	virtual void update(std::shared_ptr<Actor> owner);
	int moveCount;

	void moveOrAttack(std::shared_ptr<Actor> owner, int tx, int ty);
};
