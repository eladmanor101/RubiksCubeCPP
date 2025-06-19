#include "RubiksCube.h"

RubiksCube::RubiksCube(sf::RenderWindow& window) : window(window)
{
	// Store the indices of adjacent vertices
	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			const sf::Vector3f vi{ vertices[i] };
			const sf::Vector3f vj{ vertices[j] };
			if (abs(math::dist(vi, vj) - 2) < 0.01f)
				edge_indices.emplace_back(std::make_pair(i, j));
		}
	}
}

void RubiksCube::render(sf::RenderWindow& window)
{
	std::vector<sf::Vector2f> vertex_arr;
	for (int i = 0; i < 8; i++)
	{
		sf::Vector2f proj = projectVertex(rotateVertex(vertices[i]) + CUBE_POSITION);
		proj.x = window.getSize().x * (proj.x + 1) / 2.0f;
		proj.y = window.getSize().y * (proj.y + 1) / 2.0f;
		vertex_arr.push_back(proj);
	}

	// Sort the faces according to the average z position of their vertices
	auto comp = [this](std::pair<std::array<int, 4>, sf::Color> a, std::pair<std::array<int, 4>, sf::Color> b)
		{
			float avg1 = (vertices[a.first[0]].z + vertices[a.first[1]].z + vertices[a.first[2]].z + vertices[a.first[3]].z) / 4.0f;
			float avg2 = (vertices[b.first[0]].z + vertices[b.first[1]].z + vertices[b.first[2]].z + vertices[b.first[3]].z) / 4.0f;

			return avg1 > avg2;
		};
	std::sort(face_indices.begin(), face_indices.end(), comp);

	// Draw the faces
	for (int f = 3; f < 6; f++)
	{
		auto& face{ face_indices[f] };

		sf::ConvexShape face_shape{ 4 };
		face_shape.setFillColor(face.second);
		for (int i = 0; i < 4; i++)
		{
			face_shape.setPoint(i, vertex_arr[face.first[i]]);
			// Draw the outer edges
			for (int j = i + 1; j < 4; j++)
				paint::line(window, vertex_arr[face.first[i]], vertex_arr[face.first[j]], 5, sf::Color::Black);
		}
		window.draw(face_shape);

		// Draw the inner edges
		for (int i = 0; i < 4; i++)
		{
			int j{ (i + 1) % 4 };
			int b{ (i + 3) % 4 };
			sf::Vector3f v1{ vertices[face.first[i]] };
			sf::Vector3f v2{ vertices[face.first[j]] };
			sf::Vector3f vb{ vertices[face.first[b]] };
			sf::Vector3f offset{ (vb - v1) / 3.0f };
			v1 += offset;
			v2 += offset;
			paint::line(window, toScreenCords(v1), toScreenCords(v2), 3, sf::Color::Black);
		}
	}
}

void RubiksCube::rotate(sf::Vector2f dr)
{
	sf::Vector3f dr3{ dr.x, dr.y, 0 };
	sf::Vector3f axis{ dr3.y, -dr3.x, 0 };
	for (int i = 0; i < 8; i++)
	{
		float x = math::length(axis) / 100.0f;
		vertices[i] = rotateVertexByAxis(vertices[i], axis, x);
		vertices[i] = sqrtf(3) * math::normalize(vertices[i]);
	}
}

sf::Vector3f RubiksCube::rotateVertex(const sf::Vector3f vertex)
{
	float rotation_matrix_x[3][3]{
		{1, 0, 0},
		{0, cos(angle.x), -sin(angle.x)},
		{0, sin(angle.x), cos(angle.x)}
	};
	float rotation_matrix_y[3][3]{
		{cos(angle.y), 0, sin(angle.y)},
		{0, 1, 0},
		{-sin(angle.y), 0, cos(angle.y)}
	};
	float rotation_matrix_z[3][3]{
		{cos(angle.z), -sin(angle.z), 0},
		{sin(angle.z), cos(angle.z), 0},
		{0, 0, 1}
	};

	sf::Vector3f rotated_vertex{ vertex };
	rotated_vertex = math::multiplyByMatrix(rotated_vertex, rotation_matrix_x);
	rotated_vertex = math::multiplyByMatrix(rotated_vertex, rotation_matrix_y);
	rotated_vertex = math::multiplyByMatrix(rotated_vertex, rotation_matrix_z);

	return rotated_vertex;
}

sf::Vector3f RubiksCube::rotateVertexByAxis(sf::Vector3f v, sf::Vector3f axis, float angle)
{
	axis = math::normalize(axis);

	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	sf::Vector3f r{ v * cos_a + math::cross(axis, v) * sin_a + axis * math::dot(axis, v) * (1 - cos_a) };
	return r;
}

sf::Vector2f RubiksCube::projectVertex(const sf::Vector3f vertex)
{
	sf::Vector2f projected_vertex{ vertex.x / vertex.z, vertex.y / vertex.z };
	return projected_vertex;
}

sf::Vector3f RubiksCube::toSpaceCoords(const sf::Vector2f v, float z)
{
	sf::Vector2f proj{ v };
	proj.x = z * (v.x * 2 / window.getSize().x - 1);
	proj.y = z * (v.y * 2 / window.getSize().y - 1);
	return sf::Vector3f{ proj.x, proj.y, z };
}

sf::Vector2f RubiksCube::toScreenCords(const sf::Vector3f v)
{
	sf::Vector2f proj = projectVertex(v + CUBE_POSITION);
	proj.x = window.getSize().x * (proj.x + 1) / 2.0f;
	proj.y = window.getSize().y * (proj.y + 1) / 2.0f;
	return proj;
}