#include "Cell.h"

void Cell::clamp() {
	if (health < 0) health = 0;
}

void Cell::update() {
	if (type == PREDATOR) {
		heal(-1);
	}
	else if (type == PREY) {
		heal(1);
	}
}

void Cell::move(Cell& other) {
	other.health = health;
	other.type = type;
	type = NOTHING;
}

void Cell::reproduce(Cell& other) {
	other.health = 10;
	other.type = PREY;
}

void Cell::heal(int amount) {
	health += amount;
	clamp();
}