#include "main.hpp"

Clock::Clock(int speed) : speed(speed){}

Clock::~Clock(){}

void Clock::increment() {
	energy += speed;
}

void Clock::decrement(int cost) {
	energy -= cost;
}

int Clock::getEnergy() {
	return energy;
}

bool Clock::isReady() {
	return (energy >= e_thresh);
}