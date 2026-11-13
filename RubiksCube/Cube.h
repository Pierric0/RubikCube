#pragma once
#include "CubieRenderer.h"
class Cube
{
public:
	
	Cube(int x, int y, int z);
	void Initialize();
	void RenderCube(glm::mat4& compound);


private:
	int x, y, z;
	static CubieRenderer cubieRenderer;
	static float offset;
};

