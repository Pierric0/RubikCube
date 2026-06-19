#pragma once
#include "GameInterface.h"
#include <GL/glew.h>

class TestTriangle : public GameInterface
{
public:
	
	virtual void Initialize();
	virtual void Update(double deltaTime);
	virtual void Render(float aspectRatio);
	virtual void ClearResources();

private:
	GLuint m_shaderProgram; // Shaderprogram selbst
	GLuint m_vertexBufferObject; // 3 Positionen für dreieck
	GLuint m_arrayBufferObject; // beinhaltet vertexBufferObject, Welche Attribute, Welches Layout
	GLint m_transformLocation; 

	float m_turningAngle;
};	
	

