#pragma once
#include "GameInterface.h"
#include <GL/glew.h>

class TestTriangle : public GameInterface
{
public:
	virtual void Initialize();
	virtual void Render(float aspectRatio);
	virtual void Update(double deltaTime);
	virtual void ClearResources();

private:
	GLuint m_shaderProgram;
	GLuint m_arrayBufferObject;
	GLuint m_vertexBufferObject;
	GLint m_transformLocation;

	float m_turningAngle;
};