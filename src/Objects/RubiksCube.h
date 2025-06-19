#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../Utilities/Math.h"
#include "../Utilities/Paint.h"

class RubiksCube
{
public:
	RubiksCube(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);
	void rotate(sf::Vector2f dr);

	void debugPrint()
	{
		for (int i = 0; i < 8; i++)
		{
			std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << '\n';
		}
		std::cout << "----------------------------------------------\n";
	}

public:
	sf::Vector3f angle{ 0.0f, 0.0f, 0.0f };
	sf::Vector3f input_angle{ 0.0f, 0.0f, 0.0f };

private:
	sf::Vector3f rotateVertex(const sf::Vector3f vertex);
	sf::Vector3f rotateVertexByAxis(sf::Vector3f v, sf::Vector3f axis, float angle);
	sf::Vector2f projectVertex(const sf::Vector3f vertex);

	sf::Vector3f toSpaceCoords(const sf::Vector2f v, float z);
	sf::Vector2f toScreenCords(const sf::Vector3f v);

private:
	std::array<sf::Vector3f, 8> vertices
	{
		sf::Vector3f(-1, -1, 1),
		sf::Vector3f(1, 1, 1),
		sf::Vector3f(-1, 1, 1),
		sf::Vector3f(1, -1, 1),
		sf::Vector3f(-1, -1, -1),
		sf::Vector3f(1, 1, -1),
		sf::Vector3f(-1, 1, -1),
		sf::Vector3f(1, -1, -1)
	};
	const sf::Vector3f CUBE_POSITION{ 0, 0, 4 };

	sf::RenderWindow& window;

	std::vector<std::pair<int, int>> edge_indices;
	std::array<std::pair<std::array<int, 4>, sf::Color>, 6> face_indices
	{
		std::make_pair<>(std::array<int, 4>{2, 0, 3, 1}, sf::Color::Color(0xf8b404ff)),
		std::make_pair<>(std::array<int, 4>{6, 4, 7, 5}, sf::Color::Color(0xffffffff)),
		std::make_pair<>(std::array<int, 4>{2, 1, 5, 6}, sf::Color::Color(0xe0442cff)),
		std::make_pair<>(std::array<int, 4>{3, 0, 4, 7}, sf::Color::Color(0xfca103ff)),
		std::make_pair<>(std::array<int, 4>{3, 1, 5, 7}, sf::Color::Color(0x4084f4ff)),
		std::make_pair<>(std::array<int, 4>{2, 0, 4, 6}, sf::Color::Color(0x00bb00ff))
	};

	sf::Color values[6][3][3];
};