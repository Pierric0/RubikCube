#include "TestGlm.h"

//#include <glm/mat4x4.hpp>
//#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ShaderUtil.h"

void TestGlm::Initialize()
{
	// glm::mat4 testMat = glm::mat4(1.0f); // Muss auskommentiert werden damit eines der Beispiele funktioniert

	/* Beispiel wie Translate und rotate benutzt werden kann
	testMat = glm::translate(testMat, glm::vec3(1.0f, -1.0f, 1.0f));
	testMat = glm::rotate(testMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	testMat = testMat;
	*/

	/* Beispiel wie man die Matrix für die Kamera aufbaut
	testMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // maybe beim letzten vec3 die z-koordinate auf 1 setzen statt der y-koordinate
	testMat = glm::perspective(glm::radians(60.f), 1.0f, 0.1f, 100.0f) * testMat; // fov, aspectRatio (hier ist 1.0f falsch), kürzeste entferung, weiteste entfernung
	*/

	/* Beispiel wie man vector aus Matrix holen kann und Skalarprodukt durchführt
	testMat = glm::rotate(testMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 firstColumn = testMat[0]; // nimmt die erste Spalte (Vertikale) :: schneidet die w komponente weg (also es bleibt nur x,y und z)
	float innerProduct = glm::dot(firstColumn, firstColumn); // Skalarprodukt
	innerProduct = innerProduct;
	*/
	GLuint test = ShaderUtil::CreateShaderProgram("VSimple.glsl", "FSimple.glsl");
	m_orientationQuaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

// Hack
bool firstTimeHack = true;

void TestGlm::Update(double deltaTime)
{
	if (firstTimeHack)
	{
		firstTimeHack = false;
		return;
	}
	glm::quat rotVelocity = glm::quat(0.0f, glm::radians(180.0f), 0.0f, 0.0f); // das ist nur für die geschwindigkeit gedacht. Das ist physikalisch kein funktionierendes rotationsquaternion

	glm::quat timeDerivative = 0.5f * rotVelocity * m_orientationQuaternion;

	m_orientationQuaternion += ((float)deltaTime) * timeDerivative;

	m_orientationQuaternion = normalize(m_orientationQuaternion);

	glm::mat4 rotationMatrix = glm::mat4_cast(m_orientationQuaternion);

}
