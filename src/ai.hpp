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

	Mode aimode = HUNTING;

	Ai();  Ai(Mode mode);  ~Ai();

	virtual void update(const std::shared_ptr<Entity> &owner) = 0;
	virtual bool tryToMove(const std::shared_ptr<Entity>& owner, int tx, int ty) = 0;
};

class PlayerAi : public Ai {
public:
	int faction = 0;

	PlayerAi(); ~PlayerAi();

	void update(const std::shared_ptr<Entity>& owner);
	bool tryToMove(const std::shared_ptr<Entity>& owner,  int tx,  int ty);
};

class MeleeAi : public Ai {
public:
	int moveCount;

	MeleeAi(Ai::Mode mode);// : Ai(mode);

	void update(const std::shared_ptr<Entity>& owner);
	bool tryToMove(const std::shared_ptr<Entity>& owner, int tx, int ty);

};