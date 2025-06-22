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
    return { v / math::length(v) };
}

sf::Vector3f math::multiplyByMatrix(const Mat3f matrix, const sf::Vector3f v)
{
	sf::Vector3f r;

	r.x = math::dot(v, matrix.row(0));
	r.y = math::dot(v, matrix.row(1));
	r.z = math::dot(v, matrix.row(2));

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

Mat3f math::multiplyMatrices(const Mat3f a, const Mat3f b)
{
    Mat3f result;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            result(row, col) = math::dot(a.row(row), b.col(col));

    return result;
}

Mat3f math::getMatrixFromAxisAngle(sf::Vector3f axis, float angle)
{
    float len = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (len == 0.0f)
        return Mat3f::identity();

	axis = math::normalize(axis);

	float c = std::cos(angle);
	float s = std::sin(angle);

	Mat3f k{
		{ 0, -axis.z, axis.y },
		{ axis.z, 0, -axis.x },
		{ -axis.y, axis.x, 0 }
	};

	// Rodrigues' rotation formula
	return { Mat3f::identity() + s * k + (1.0f - c) * math::multiplyMatrices(k, k) };
}