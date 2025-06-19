#include <iostream>
#include <SFML/Graphics.hpp>

#include "Utilities/Math.h"

#include "Objects/RubiksCube.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Rubiks Cube");

	RubiksCube cube{ window };

	sf::Vector2f prev_mouse_pos;
	sf::Vector2f curr_mouse_pos;
	sf::Vector2f diff_mouse_pos;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left);
					//cube.mouse_held_pos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
				break;
			}
		}
		prev_mouse_pos = curr_mouse_pos;
		curr_mouse_pos = sf::Vector2f{ sf::Mouse::getPosition(window) };
		diff_mouse_pos = curr_mouse_pos - prev_mouse_pos;

		float dt = clock.restart().asSeconds();

		//cube.angle.x += dt * math::PI / 6;
		//cube.angle.y += dt * math::PI / 8;
		//cube.angle.z += dt * math::PI / 7;

		//cube.debugPrint();

		window.clear();
		if (window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && diff_mouse_pos.x * diff_mouse_pos.x + diff_mouse_pos.y * diff_mouse_pos.y > 0.0001f)
			cube.rotate(diff_mouse_pos);
		cube.render(window);
		window.display();
	}

	return 0;
}