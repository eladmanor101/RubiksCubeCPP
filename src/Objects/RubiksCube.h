#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../Utilities/Math.h"
#include "../Utilities/Paint.h"

const sf::Color EDGE_COLOR{ sf::Color::Magenta };
const int EDGE_THICKNESS{ 3 };

enum class FaceColors {
	WHITE, YELLOW, GREEN, RED, BLUE, ORANGE
};

// Represents a single corner/edge/center piece
struct Cubelet
{
	sf::Vector3f position; // Relative to the cube center
	std::array<std::optional<FaceColors>, 6> face_colors; // white, yellow, green, red, blue, orange (positions)
};

constexpr int face_indices[][]{ {4, 5, 6, 7}, {0, 1, 2, 3}, {} };

class RubiksCube
{
public:
	RubiksCube(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);
	void rotate(sf::Vector2f dr);

public:
	Mat3f rotation_matrix{ Mat3f::identity() };

private:
	sf::Vector3f rotateVertex(const sf::Vector3f vertex);
	sf::Vector3f rotateVertexByAxis(sf::Vector3f v, sf::Vector3f axis, float angle);
	sf::Vector2f projectVertex(const sf::Vector3f vertex);

	sf::Vector3f toSpaceCoords(const sf::Vector2f v, float z);
	sf::Vector2f toScreenCords(const sf::Vector3f v);

private:
	std::array<Cubelet, 26> cubelets{};

	// 0-3 and 4-7 are faces, where indices i, i+4 are connected with an edge between the faces
	std::array<sf::Vector3f, 8> original_vertices
	{
		sf::Vector3f(-0.5, -0.5, 0.5),	// front bottom left
		sf::Vector3f(-0.5, 0.5, 0.5),	// front top left
		sf::Vector3f(0.5, 0.5, 0.5),	// front top right
		sf::Vector3f(0.5, -0.5, 0.5),	// front bottom right
		sf::Vector3f(-0.5, -0.5, -0.5),	// back bottom left
		sf::Vector3f(-0.5, 0.5, -0.5),	// back top left
		sf::Vector3f(0.5, 0.5, -0.5),	// back top right
		sf::Vector3f(0.5, -0.5, -0.5)	// back bottom right
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