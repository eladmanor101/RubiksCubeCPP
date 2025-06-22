#pragma once

#include <SFML/Graphics.hpp>

class Mat3f
{
public:
	Mat3f();
	Mat3f(float v[9]);
	Mat3f(sf::Vector3f r1, sf::Vector3f r2, sf::Vector3f r3);

	float& operator() (int r, int c) { return m[r * 3 + c]; }
	const float operator() (int r, int c) const { return m[r * 3 + c]; }
	Mat3f operator+(const Mat3f& other) const;
	Mat3f operator*(float scalar) const;
	friend Mat3f operator*(float scalar, const Mat3f& mat);

	sf::Vector3f row(int r) const { return { m[r * 3], m[r * 3 + 1], m[r * 3 + 2] }; }
	sf::Vector3f col(int c) const { return { m[c], m[c + 3], m[c + 6] }; }

	static Mat3f identity();

private:
	float m[9];
};