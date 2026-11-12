#pragma once
#include "CubieRenderer.h"
#include "GameInterface.h"
#include "InputSystem.h"
#include "Cube.h"
#include <glm/ext/quaternion_float.hpp>
#include <glm/vec3.hpp>

class CompoundCube : public GameInterface
{
public:
	virtual void Initialize(GLFWwindow* window);
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);
	virtual void UpdateCubePositions(int axis, int side, float rotation);


private:
	CubieRenderer m_cubieRenderer;
	//float m_turningAngle;
	InputSystem m_input;
	glm::quat m_orientationQuaternion;
	Cube m_cubePositions[27];
};



