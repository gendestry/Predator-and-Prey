#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>

#include "Config.h"
#include "Cell.h"

class Board {
private:
	sf::RectangleShape rect;
	std::vector<Cell> cells;

	inline int getIndex(int x, int y) {
		return x + y * WIDTH / CELL_SIZE;
	}

public:
	Board();

	void update();
	void updatePrey(Cell& first, Cell& next);
	void updatePredator(Cell& first, Cell& next);
	void render(sf::RenderWindow &window);
	void addCell(int x, int y, bool type);
};