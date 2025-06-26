#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../Utilities/Math.h"
#include "../Utilities/Paint.h"

/*
* X axis is horizontal (right - positive)
* Y axis is vertical   (down - positive)
* Z axis is depth      (inward - positive)
*/

const sf::Color EDGE_COLOR{ sf::Color::Black };
const int EDGE_THICKNESS{ 3 };

enum class FaceColors {
	WHITE, YELLOW, GREEN, RED, BLUE, ORANGE
};

enum class Faces {
	U, D, F, R, B, L
};

constexpr FaceColors DEFAULT_FACE_COLORS[]{ FaceColors::WHITE, FaceColors::YELLOW, FaceColors::GREEN, FaceColors::RED, FaceColors::BLUE, FaceColors::ORANGE };

constexpr sf::Color FACE_SF_COLORS[]{ sf::Color::White, sf::Color::Yellow, sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color(0xed5f00ff) };

// Represents a single corner/edge/center piece
struct Cubelet
{
	sf::Vector3f position; // Relative to the cube center
	std::array<std::optional<FaceColors>, 6> face_colors; // U, D, F, R, B, L
};

constexpr int face_indices[][4]{
	{1, 2, 6, 5}, // U
	{4, 7, 3, 0}, // D
	{3, 2, 1, 0}, // F
	{2, 3, 7, 6}, // R
	{4, 5, 6, 7}, // B
	{0, 1, 5, 4}, // L
};

class RubiksCube
{
public:
	RubiksCube(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);
	void rotate(sf::Vector2f dr);

public:
	Mat3f rotation_matrix{ Mat3f::identity() };

private:
	sf::Vector3f rotateVertexByAxis(sf::Vector3f v, sf::Vector3f axis, float angle);
	sf::Vector3f normal(const Cubelet& cubelet, int face_index);

private:
	std::array<Cubelet, 26> cubelets{};

	// 0-3 and 4-7 are faces, where indices i, i+4 are connected with an edge between the faces
	std::array<sf::Vector3f, 8> original_vertices
	{
		sf::Vector3f{ -0.5,  0.5, -0.5 },	// front bottom left
		sf::Vector3f{ -0.5, -0.5, -0.5 },	// front top left
		sf::Vector3f{  0.5, -0.5, -0.5 },	// front top right
		sf::Vector3f{  0.5,  0.5, -0.5 },	// front bottom right
		sf::Vector3f{ -0.5,  0.5,  0.5 },	// back bottom left
		sf::Vector3f{ -0.5, -0.5,  0.5 },	// back top left
		sf::Vector3f{  0.5, -0.5,  0.5 },	// back top right
		sf::Vector3f{  0.5,  0.5,  0.5 }	// back bottom right
	};

	sf::RenderWindow& window;
};