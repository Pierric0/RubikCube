#pragma once
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <vector>

class CubieRenderer
{
public:
	void Initialize();
	void Render(const glm::mat4& transformationMatrix); // mit der Matrix wird der Mittelpunkt des cubi angegeben
	void ClearResources();

private:
	const float m_offset = 0.5f; // vom mittelpunkt. Daher ist er bei 0.5f genau 1x1x1 groß

	void AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray); 
	void AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray);
	void TranscribeToFloatArray(std::vector <glm::vec3>& vecArray, float* floatArray);

	GLuint m_shaderProgram; // Shaderprogram selbst
	GLuint m_vertexBufferObject[2]; // Position und Farbe
	GLuint m_arrayBufferObject; // beinhaltet vertexBufferObject, Welche Attribute, Welches Layout
	GLint m_transformLocation;
};

