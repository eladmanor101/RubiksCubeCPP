#pragma once

#include <SFML/Graphics.hpp>

namespace paint
{
	void line(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, int thickness, sf::Color color);
}
