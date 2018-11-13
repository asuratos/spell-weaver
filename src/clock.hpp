#pragma once

class Clock {
public:
	int walkCost = 50;

	void increment();
	void decrement(int cost);

	bool isReady();

	int getEnergy();

	Clock(int speed); ~Clock();
protected:
	int speed;
	int energy = 100;
	int e_thresh = 100;
};