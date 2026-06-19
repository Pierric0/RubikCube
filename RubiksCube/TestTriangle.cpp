#include "TestTriangle.h"
#include "ShaderUtil.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void TestTriangle::Initialize()
{
	m_turningAngle = 0;

	const float positions[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	m_shaderProgram = ShaderUtil::CreateShaderProgram("VSimple.glsl", "FSimple.glsl");
	m_transformLocation = glGetUniformLocation(m_shaderProgram, "transformation"); // findet die transformationsmatrix id in VSimple.glsl

	glGenVertexArrays(1, &m_arrayBufferObject); // erzeugt ein VAO ([Vertex]ArrayBuffer)
	glGenBuffers(1, &m_vertexBufferObject); // erzeugt ein (leeres) VBO (VertexBufferObject) bereit

	glBindVertexArray(m_arrayBufferObject); // VAO aktivieren, alles folgende wir hierein gespeichert
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject); // VBO wird aktiviert
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); // vertexdaten werden hochgeladen an den aktuell gebundenen VBO


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 	// wie die Daten, die hochgeladen wurden, interpretiert werden; index 0 für Shader; 3 Komponenten für jeden Vertex; Datentyp; Normalisieren (hier nein); wie viele bytes gesprungen werden für nächsten vertex daten block; bei welchem byte anfangen

	glEnableVertexAttribArray(0); // location 0 aktivieren (ist die 0 location in Shader)
	glBindVertexArray(0); // VAO deaktiveren
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO deaktivieren
}

void TestTriangle::Update(double deltaTime)
{
	m_turningAngle += glm::radians(120.0f) * ((float)deltaTime);

}

void TestTriangle::Render(float aspectRatio)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_arrayBufferObject);

	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) *
		glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * 
		glm::rotate(glm::mat4(1.0f), m_turningAngle, glm::vec3(0.0f,0.0f,1.0f)); // transformation erzeugt

	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(globalTransformation)); // transformation im Shader gesetzt (ist dafür da das das dreieck vor die kamera bewegt wird)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}

void TestTriangle::ClearResources()
{
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteVertexArrays(1, &m_arrayBufferObject);
	glDeleteProgram(m_shaderProgram);
}
