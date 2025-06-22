#include "Mat3f.h"

Mat3f::Mat3f() : m{}
{}

Mat3f::Mat3f(float v[9])
	: m{ v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8] }
{}

Mat3f::Mat3f(sf::Vector3f r1, sf::Vector3f r2, sf::Vector3f r3)
	: m{ r1.x, r1.y, r1.z, r2.x, r2.y, r2.z, r3.x, r3.y, r3.z }
{}

Mat3f Mat3f::identity()
{
	return {
		sf::Vector3f{ 1.0f, 0.0f, 0.0f },
		sf::Vector3f{ 0.0f, 1.0f, 0.0f },
		sf::Vector3f{ 0.0f, 0.0f, 1.0f }
	};
}

Mat3f Mat3f::operator+(const Mat3f& other) const
{
	Mat3f result;

	for (int i = 0; i < 9; i++)
		result.m[i] = m[i] + other.m[i];

	return result;
}

Mat3f Mat3f::operator*(float scalar) const
{
	Mat3f result;

	for (int i = 0; i < 9; i++)
		result.m[i] = m[i] * scalar;

	return result;
}

Mat3f operator*(float scalar, const Mat3f& mat)
{
	return mat * scalar;
}