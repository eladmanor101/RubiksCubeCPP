#include "Math.h"

float math::dist(const sf::Vector3f v1, const sf::Vector3f v2)
{
	sf::Vector3f diff = v1 - v2;
	return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

float math::length(const sf::Vector3f v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
float math::length(const sf::Vector2f v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

sf::Vector3f math::normalize(const sf::Vector3f v)
{
	sf::Vector3f r{ v / length(v) };
	return r;
}

sf::Vector3f math::multiplyByMatrix(const sf::Vector3f v, const float matrix[3][3])
{
	sf::Vector3f r;

	r.x = math::dot(v, toVec(matrix[0]));
	r.y = math::dot(v, toVec(matrix[1]));
	r.z = math::dot(v, toVec(matrix[2]));

	return r;
}

float math::dot(const sf::Vector3f v1, const sf::Vector3f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

sf::Vector3f math::cross(const sf::Vector3f v1, const sf::Vector3f v2)
{
	sf::Vector3f r;

	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = v1.z * v2.x - v1.x * v2.z;
	r.z = v1.x * v2.y - v1.y * v2.x;

	return r;
}

sf::Vector3f math::toVec(const float v[3])
{
	return sf::Vector3f(v[0], v[1], v[2]);
}