#include "RubiksCube.h"

#include "../Utilities/Transform.h"

sf::Vector3f RubiksCube::normal(const Cubelet& cubelet, int face_index)
{
	sf::Vector3f face_vertices_3d[4];
	for (int j = 0; j < 4; j++)
		face_vertices_3d[j] = transform::rotateVertex(
			original_vertices[face_indices[face_index][j]] + cubelet.position,
			rotation_matrix
		);

	sf::Vector3f diff1 = face_vertices_3d[1] - face_vertices_3d[0];
	sf::Vector3f diff2 = face_vertices_3d[2] - face_vertices_3d[1];
	sf::Vector3f face_normal{ math::normalize(math::cross(diff1, diff2)) };

	return face_normal;
}

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
				if (i == 1) cubelets[index].face_colors[static_cast<size_t>(Faces::R)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::R)];
				if (i == -1) cubelets[index].face_colors[static_cast<size_t>(Faces::L)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::L)];
				if (j == 1) cubelets[index].face_colors[static_cast<size_t>(Faces::D)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::D)];
				if (j == -1) cubelets[index].face_colors[static_cast<size_t>(Faces::U)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::U)];
				if (k == 1) cubelets[index].face_colors[static_cast<size_t>(Faces::B)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::B)];
				if (k == -1) cubelets[index].face_colors[static_cast<size_t>(Faces::F)] = DEFAULT_FACE_COLORS[static_cast<size_t>(Faces::F)];
			}
		}
	}
}

void RubiksCube::render(sf::RenderWindow& window)
{
	auto cmp = [this](Cubelet a, Cubelet b)
	{
		sf::Vector3f a_vertices[4];
		for (int i = 0; i < 4; i++)
			a_vertices[i] = transform::rotateVertex(
				original_vertices[i] + a.position,
				rotation_matrix
			);
		sf::Vector3f b_vertices[4];
		for (int i = 0; i < 4; i++)
			b_vertices[i] = transform::rotateVertex(
				original_vertices[i] + b.position,
				rotation_matrix
			);

		float a_sum = a_vertices[0].z + a_vertices[1].z + a_vertices[2].z + a_vertices[3].z;
		float b_sum = b_vertices[0].z + b_vertices[1].z + b_vertices[2].z + b_vertices[3].z;

		return a_sum > b_sum;
	};

	std::sort(cubelets.begin(), cubelets.end(), cmp);

	for (const Cubelet& cubelet : cubelets)
	{
		// Apply 3D transformation and project onto the screen
		std::array<sf::Vector2f, 8> projected_vertices;
		for (int i = 0; i < 8; i++)
		{
			projected_vertices[i] = transform::applyTransformations(
				window,
				original_vertices[i] + cubelet.position,
				rotation_matrix
			);
		}

		// Draw edges
		for (int i = 0; i < 4; i++)
		{
			paint::line(window, projected_vertices[i], projected_vertices[(i + 1) % 4], EDGE_THICKNESS, EDGE_COLOR);
			paint::line(window, projected_vertices[i + 4], projected_vertices[(i + 1) % 4 + 4], EDGE_THICKNESS, EDGE_COLOR);
			paint::line(window, projected_vertices[i], projected_vertices[i + 4], EDGE_THICKNESS, EDGE_COLOR);
		}

		// Draw faces
		for (int i = 0; i < 6; i++)
		{
			sf::Vector3f face_vertices_3d[4];
			for (int j = 0; j < 4; j++)
				face_vertices_3d[j] = transform::rotateVertex(
					original_vertices[face_indices[i][j]] + cubelet.position,
					rotation_matrix
				);

			sf::Vector3f face_normal{ normal(cubelet, i) };

			if (math::dot(face_normal, face_vertices_3d[0] + transform::CUBE_POSITION) < 0) // DOT with camera direction
			{
				sf::Vector2f face_vertices_2d[4];
				for (int j = 0; j < 4; j++)
					face_vertices_2d[j] = transform::toScreenCoords(window, face_vertices_3d[j], transform::CUBE_POSITION);

				if (cubelet.face_colors[i].has_value())
				{
					sf::Color color{ FACE_SF_COLORS[static_cast<size_t>(cubelet.face_colors[i].value())] };
					paint::rect(window, face_vertices_2d, color);
				}
			}
		}
	}
}

void RubiksCube::rotate(sf::Vector2f dr)
{
	sf::Vector3f axis{ dr.y, -dr.x, 0 };
	float angle = math::length(dr) / 100.0f;

	rotation_matrix = math::multiplyMatrices(math::getMatrixFromAxisAngle(axis, angle), rotation_matrix);
}

sf::Vector3f RubiksCube::rotateVertexByAxis(sf::Vector3f v, sf::Vector3f axis, float angle)
{
	axis = math::normalize(axis);

	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	sf::Vector3f r{ v * cos_a + math::cross(axis, v) * sin_a + axis * math::dot(axis, v) * (1 - cos_a) };
	return r;
}