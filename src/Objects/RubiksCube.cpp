#include "RubiksCube.h"

RubiksCube::RubiksCube(sf::RenderWindow& window) : window(window)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (i == 0 && j == 0 && k == 0)
					continue;

				int index = (i + 1) * 9 + (j + 1) * 3 + (k + 1);
				if (index > 12) index--;

				cubelets[index].position = sf::Vector3f(i, j, k);

				// Initial cubelets face colors
				if (i == 1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::RED)] = FaceColors::RED;
				if (i == -1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::ORANGE)] = FaceColors::ORANGE;
				if (j == 1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::WHITE)] = FaceColors::WHITE;
				if (j == -1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::YELLOW)] = FaceColors::YELLOW;
				if (k == 1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::BLUE)] = FaceColors::BLUE;
				if (k == -1) cubelets[index].face_colors[static_cast<size_t>(FaceColors::GREEN)] = FaceColors::GREEN;
			}
		}
	}
}

void RubiksCube::render(sf::RenderWindow& window)
{
	for (const Cubelet& cubelet : cubelets)
	{
		// Apply 3D transformation and project onto the screen
		std::array<sf::Vector2f, 8> projected_vertices;
		for (int i = 0; i < 8; i++)
		{
			projected_vertices[i] = toScreenCords(
				rotateVertex(
					original_vertices[i] + cubelet.position
				) + CUBE_POSITION
			);
		}

		// Draw edges
		for (int i = 0; i < 4; i++)
		{
			paint::line(window, projected_vertices[i], projected_vertices[(i + 1) % 4], EDGE_THICKNESS, EDGE_COLOR);
			paint::line(window, projected_vertices[i + 4], projected_vertices[(i + 1) % 4 + 4], EDGE_THICKNESS, EDGE_COLOR);
			paint::line(window, projected_vertices[i], projected_vertices[i + 4], EDGE_THICKNESS, EDGE_COLOR);
		}
	}

	/*
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
	*/
}

void RubiksCube::rotate(sf::Vector2f dr)
{
	sf::Vector3f axis{ dr.y, -dr.x, 0 };
	float angle = math::length(dr) / 100.0f;

	rotation_matrix = math::multiplyMatrices(math::getMatrixFromAxisAngle(axis, angle), rotation_matrix);
}

sf::Vector3f RubiksCube::rotateVertex(const sf::Vector3f vertex)
{
	return math::multiplyByMatrix(rotation_matrix, vertex);
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
	return { vertex.x / vertex.z, vertex.y / vertex.z };
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