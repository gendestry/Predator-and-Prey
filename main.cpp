#include <SFML\Graphics.hpp>
#include "Config.h"
#include "Board.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Predator and Prey");

	Board board;

	// window.setFramerateLimit(10);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				board.addCell(localPosition.x / CELL_SIZE, localPosition.y / CELL_SIZE, true);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				board.addCell(localPosition.x / CELL_SIZE, localPosition.y / CELL_SIZE, false);
			}
		}

		window.clear();

		board.update();
		board.render(window);

		window.display();
	}

	return 0;
}