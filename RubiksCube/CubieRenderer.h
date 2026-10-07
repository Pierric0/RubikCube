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

	float GetCubieExtension() const { return 2.0f * m_offset;  }

private:
	const float m_offset = 0.5f; // vom mittelpunkt. Daher ist er bei 0.5f genau 1x1x1 groß

	// sideType ist 0,1 oder 2 für x,y oder z und direction ist für eine der beiden seiten dann (-1 und 1)
	// PositionArray sind die vertices von der Seite selbst (6 vertices für das quadrat da es aus zwei dreiecken besteht)
	void AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray); 
	// genau das gleiche wie AddSidePosition aber für farbe
	void AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray);
	// macht aus dem vec3 array ein floatarray weil opengl nicht mit dem vecarray klar kommt
	void TranscribeToFloatArray(std::vector <glm::vec3>& vecArray, float* floatArray);

	GLuint m_shaderProgram; // Shaderprogram selbst
	GLuint m_vertexBufferObject[2]; // Position und Farbe
	GLuint m_arrayBufferObject; // beinhaltet vertexBufferObject, Welche Attribute, Welches Layout
	GLint m_transformLocation;
};

