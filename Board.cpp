#include "Board.h"

Board::Board() {
	srand(time(nullptr));
	rect.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));

	Cell cell;

	for (int i = 0; i < ARR_SIZE; i++) {
		int n = rand() % 1000;
		if (n > 100) {
			cell.type = Cell::NOTHING;
		}
		else if (n > 50) {
			cell.type = Cell::PREY;
		}
		else {
			cell.type = Cell::PREDATOR;
		}
		cells.push_back(cell);
	}
}

void Board::update() {
	for (int y = 0; y < HEIGHT / CELL_SIZE; y++) {
		for (int x = 0; x < WIDTH / CELL_SIZE; x++) {
			int index = getIndex(x, y);
			Cell& thisCell = cells[index];
			
			if (thisCell.type == Cell::NOTHING)
				continue;
			
			int xChange = (rand() % 3) - 1; // [0,1,2] - 1 --> [-1,0,1]
			int yChange = (rand() % 3) - 1;
			int xCell = x + xChange;
			int yCell = y + yChange;

			if (xCell < 0 || xCell >= WIDTH / CELL_SIZE) continue;
			if (yCell < 0 || yCell >= HEIGHT / CELL_SIZE) continue;
			
			int nextIndex = getIndex(xCell, yCell);
			Cell &nextCell = cells[nextIndex];
			
			thisCell.update();
			
			if (thisCell.type == Cell::PREY) {
				updatePrey(thisCell, nextCell);
			}
			else {
				updatePredator(thisCell, nextCell);
			}

		}
	}
}

void Board::updatePrey(Cell& first, Cell& next) {
	bool reproduce = false;

	if (first.health >= MAX_HEALTH) {
		first.health = 10;
		reproduce = true;
	}

	if (next.type == Cell::NOTHING && reproduce) {
		first.reproduce(next);
	}
}

void Board::updatePredator(Cell& first, Cell& next) {
	if (first.health <= 0) {
		first.type = Cell::NOTHING;
	}

	if (next.type == Cell::PREY) {
		next.type = Cell::PREDATOR;
		first.heal(next.health);
	}
	else if (next.type == Cell::NOTHING) {
		first.move(next);
	}
}

void Board::render(sf::RenderWindow &window) {
	for (int y = 0; y < HEIGHT / CELL_SIZE; y++) {
		for (int x = 0; x < WIDTH / CELL_SIZE; x++) {
			rect.setPosition(x * CELL_SIZE, y * CELL_SIZE);
			//sf::Uint8 color = (cells[getIndex(x, y)].health / MAX_HEALTH) * 255;
			if (cells[getIndex(x, y)].type == Cell::NOTHING) {
				rect.setFillColor(sf::Color::Black);
			}
			else if (cells[getIndex(x, y)].type == Cell::PREY) {
				//rect.setFillColor(sf::Color(0, color, 0));
				//rect.setFillColor(sf::Color(0, cells[getIndex(x, y)].health * 12, 0)); // temp
				rect.setFillColor(sf::Color::Green);
			}
			else {
				rect.setFillColor(sf::Color::Red);
				//rect.setFillColor(sf::Color(color, 0, 0));
			}
			window.draw(rect);
		}
	}
}

void Board::addCell(int x, int y, bool type) {
	// std::cout << getIndex(x, y);
	if(type)
		cells[getIndex(x, y)].type = Cell::PREDATOR;
	else
		cells[getIndex(x, y)].type = Cell::PREY;
	cells[getIndex(x, y)].health = 20;
}