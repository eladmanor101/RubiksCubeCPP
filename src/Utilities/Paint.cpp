#include "Paint.h"

#include "Math.h"

void paint::line(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, int thickness = 1.0f, sf::Color color = sf::Color::White)
{
	sf::Vector2f dir{ end - start };
	float dir_length{ math::length(dir) };
	sf::Vector2f dir_norm{ dir / dir_length };
	sf::Vector2f dir_perp_norm{ -dir_norm.y, dir_norm.x };
	sf::Vector2f dir_perp{ dir_perp_norm * (thickness / 2.0f) };

	sf::Vertex vertices[4];
	vertices[0].position = start + dir_perp;
	vertices[1].position = end + dir_perp;
	vertices[2].position = end - dir_perp;
	vertices[3].position = start - dir_perp;

	for (int i = 0; i < 4; i++)
		vertices[i].color = color;

	window.draw(vertices, 4, sf::Quads);
}