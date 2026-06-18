#pragma once
#include "GameInterface.h"
#include <GL/glew.h>

class TestTriangle : public GameInterface
{
public:
	
	virtual void Initialize();
	virtual void Render(float aspectRatio);
	virtual void ClearResources();

private:
	GLuint m_shaderProgram; // Shaderprogram selbst
	GLuint m_vertexBufferObject; // 3 Positionen für dreieck
	GLuint m_arrayBufferObject; // beinhaltet vertexBufferObject und wie es zu interpretieren ist
	GLint m_transormLocation; 
};	
	

