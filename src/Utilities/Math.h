#pragma once

#include <SFML/Graphics.hpp>

#include "Types/Mat3f.h"

namespace math
{
	const double PI = 3.14159265358979323846;

	float dist(const sf::Vector3f v1, const sf::Vector3f v2);

	float length(const sf::Vector3f v);
	float length(const sf::Vector2f v);

	sf::Vector3f normalize(const sf::Vector3f v);

	sf::Vector3f multiplyByMatrix(const Mat3f& matrix, const sf::Vector3f v);

	float dot(const sf::Vector3f v1, const sf::Vector3f v2);

	sf::Vector3f cross(const sf::Vector3f v1, const sf::Vector3f v2);

	Mat3f multiplyMatrices(const Mat3f& a, const Mat3f& b);

	Mat3f getMatrixFromAxisAngle(sf::Vector3f axis, float angle);
}