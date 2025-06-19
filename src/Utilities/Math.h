#pragma once

#include <SFML/Graphics.hpp>

namespace math
{
	const double PI = 3.14159265358979323846;

	float dist(const sf::Vector3f v1, const sf::Vector3f v2);

	float length(const sf::Vector3f v);
	float length(const sf::Vector2f v);

	sf::Vector3f normalize(const sf::Vector3f v);

	sf::Vector3f multiplyByMatrix(const sf::Vector3f v, const float matrix[3][3]);

	float dot(const sf::Vector3f v1, const sf::Vector3f v2);

	sf::Vector3f cross(const sf::Vector3f v1, const sf::Vector3f v2);

	sf::Vector3f toVec(const float v[3]);
}