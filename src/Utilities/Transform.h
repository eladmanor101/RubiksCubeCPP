#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace transform
{
	constexpr sf::Vector3f CUBE_POSITION{ 0, 0, 4 };

	sf::Vector2f projectVertex(sf::Vector3f vertex)
	{
		return { vertex.x / vertex.z, vertex.y / vertex.z };
	}

	sf::Vector3f rotateVertex(sf::Vector3f vertex, const Mat3f& rotation_matrix)
	{
		return math::multiplyByMatrix(rotation_matrix, vertex);
	}

	sf::Vector3f toSpaceCoords(const sf::RenderWindow& window, sf::Vector2f v, float z)
	{
		sf::Vector2f proj{ v };
		proj.x = z * (v.x * 2 / window.getSize().x - 1);
		proj.y = z * (v.y * 2 / window.getSize().y - 1);
		return sf::Vector3f{ proj.x, proj.y, z };
	}

	sf::Vector2f toScreenCoords(const sf::RenderWindow& window, sf::Vector3f v)
	{
		sf::Vector2f proj = transform::projectVertex(v + CUBE_POSITION);
		proj.x = window.getSize().x * (proj.x + 1) / 2.0f;
		proj.y = window.getSize().y * (proj.y + 1) / 2.0f;
		return proj;
	}

	sf::Vector2f toScreenCoords(const sf::RenderWindow& window, sf::Vector3f v, sf::Vector3f offset)
	{
		return transform::toScreenCoords(window, v + offset);
	}

	sf::Vector2f applyTransformations(const sf::RenderWindow& window, sf::Vector3f vertex, const Mat3f& rotation_matrix)
	{
		return transform::toScreenCoords(
			window,
			transform::rotateVertex(vertex, rotation_matrix) + CUBE_POSITION
		);
	}
}