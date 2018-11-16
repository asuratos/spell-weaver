#pragma once
#include "main.hpp"

//template<class T>
class Ai {
public:
//	bool friendly;
	int faction;
	enum Mode {
		CONTROLLED,
		ASLEEP,
		HUNTING,
		AFRAID
	};

	~Ai();

	virtual void update(std::shared_ptr<Entity> owner) = 0;
	virtual bool tryToMove(std::shared_ptr<Entity> owner, int tx, int ty) = 0;
};

class PlayerAi : public Ai {
public:

	PlayerAi(); ~PlayerAi();

	virtual void update(std::shared_ptr<Entity> owner);
	bool tryToMove(std::shared_ptr<Entity> owner,  int tx,  int ty);
};

class MeleeAi : public Ai {
public:
	int moveCount;

	MeleeAi(Ai::Mode mode);

	void update(std::shared_ptr<Entity> owner);
	bool tryToMove(std::shared_ptr<Entity> owner, int tx, int ty);

};