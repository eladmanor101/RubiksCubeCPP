#include "Paint.h"

#include "Math.h"

void paint::line(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, int thickness = 1.0f, sf::Color color = sf::Color::White)
{
	sf::Vector2f dir{ end - start };
	float dir_length{ math::length(dir) };

	if (dir_length == 0) return;

	sf::Vector2f dir_norm{ dir / dir_length };
	sf::Vector2f dir_perp_norm{ -dir_norm.y, dir_norm.x };
	sf::Vector2f dir_perp{ dir_perp_norm * (thickness / 2.0f) };

	sf::VertexArray first_triangle(sf::PrimitiveType::Triangles, 3);
	sf::VertexArray second_triangle(sf::PrimitiveType::Triangles, 3);
	first_triangle[0].position = start + dir_perp;
	first_triangle[1].position = end + dir_perp;
	first_triangle[2].position = end - dir_perp;
	second_triangle[0].position = start + dir_perp;
	second_triangle[1].position = end - dir_perp;
	second_triangle[2].position = start - dir_perp;

	for (int i = 0; i < 3; i++)
	{
		first_triangle[i].color = color;
		second_triangle[i].color = color;
	}

	window.draw(first_triangle);
	window.draw(second_triangle);
}

void paint::rect(sf::RenderWindow& window, sf::Vector2f vertices[], sf::Color fill_color)
{
	sf::ConvexShape rect(4);

	for (int i = 0; i < 4; i++)
		rect.setPoint(i, vertices[i]);

	rect.setFillColor(fill_color);

	window.draw(rect);
}
