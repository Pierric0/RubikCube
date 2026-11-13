#include "Cube.h"
#include "CubieRenderer.h"
#include <glm/ext/matrix_transform.hpp>

CubieRenderer Cube::cubieRenderer;
float Cube::offset = 0.0f;

Cube::Cube(int X, int Y, int Z)
{
	x = X;
	y = Y;
	z = Z;
}

void Cube::Initialize()
{
	cubieRenderer.Initialize();
	offset = cubieRenderer.GetCubieExtension() + 0.1f;
}

void Cube::RenderCube(glm::mat4& compound)
{
	compound = glm::translate(compound, glm::vec3((x - 1) * offset, (y - 1) * offset, (z - 1) * offset));
	cubieRenderer.Render(compound);
}