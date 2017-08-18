#pragma once
#include "Config.h"

class Cell {
private:
	void clamp();
public:
	int health = MAX_HEALTH;

	enum CellType {
		PREDATOR,
		PREY,
		NOTHING
	} type;

	void update();
	void heal(int amount);
	void move(Cell& other);
	void reproduce(Cell& other);
};