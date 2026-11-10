#include "CompoundCube.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

void CompoundCube::Initialize(GLFWwindow* window)
{
	m_input.SetWindow(window);
	m_input.ObserveKey(GLFW_KEY_SPACE);
	m_input.ObserveKey(GLFW_KEY_D);
	m_input.ObserveKey(GLFW_KEY_A);
	m_input.ObserveKey(GLFW_KEY_W);
	m_input.ObserveKey(GLFW_KEY_S);
	m_input.ObserveKey(GLFW_KEY_E);
	m_input.ObserveKey(GLFW_KEY_Q);
	
	m_cubieRenderer.Initialize();
	
}

void CompoundCube::Render(float aspectRatio)
{
	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) * // zuständig ein 3d objekt auf einem 2d bildschirm perspektivisch anzuzeigen : Projection-Matrix
		glm::lookAt(glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * // zuständig die Kamera zu setzen (theoretisch dreht und verschiebt das hier auch den Cube aber man kann sich vorstellen das die Kamera hier gesetzt wird) : View-Matrix
		glm::mat4_cast(m_orientationQuaternion); // zuständig den würfel aus dem local space in den global Space zu drehen (dadurch das wir quaternions benutzen casten wir das einfach auf eine matrix anstatt hier extra rotation() auszuführen) (translation wird später im code, tatsächlich aber durch rechts nach links regel früher, durchgeführt) : Modell-Matrix

	float offset = m_cubieRenderer.GetCubieExtension() +0.1f;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				if (i == 1 && j == 1 && k == 1)
				{
					continue;
				}

				//ist tatsächlich so gewollt damit wir die cubeplätze uns merken können (noch nicht sicher)
				glm::mat4 compound = globalTransformation; //A
				//glm::mat4 compound = glm::translate(globalTransformation, glm::vec3((i - 1) * offset, (j - 1) * offset, (k - 1) * offset)); //B
				
				/*if (i == 0) {
					compound = glm::rotate(compound, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				}*/
				compound = glm::rotate(compound, glm::radians(45.0f) * (i % 2), glm::vec3(1.0f, 0.0f, 0.0f));
				//compound = glm::rotate(compound, glm::radians(90.0f) * (j % 2), glm::vec3(0.0f, 1.0f, 0.0f));
				//compound = glm::rotate(compound, glm::radians(90.0f) * (k % 2), glm::vec3(0.0f, 0.0f, 1.0f));
				

				// i geht nach links, j nach oben, und k nach hinten (also ist 0,0,0 der cube der unten rechts ganz vorne ist)
				
				
				compound = glm::translate(compound, glm::vec3((i - 1) * offset, (j - 1) * offset, (k - 1) * offset)); //Verschiebt die Cubie dann tatsächlich vom local Space in den global Space //A
				
				m_cubieRenderer.Render(compound);
			}
		}
	}


}

void CompoundCube::ClearResources()
{
	m_cubieRenderer.ClearResources();
}

void CompoundCube::Update(double deltaTime)
{
	m_input.Update();
	if (m_input.WasKeyPressed(GLFW_KEY_SPACE))
		m_orientationQuaternion = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	float xVel = 0.0f;
	if (m_input.IsKeyDown(GLFW_KEY_W))
	{
		xVel = glm::radians(90.0f);
	}
	if (m_input.IsKeyDown(GLFW_KEY_S))
	{
		xVel = glm::radians(-90.0f);
	}

	float yVel = 0.0f;
	if (m_input.IsKeyDown(GLFW_KEY_A))
	{
		yVel = glm::radians(-90.0f);
	}
	if (m_input.IsKeyDown(GLFW_KEY_D))
	{
		yVel = glm::radians(90.0f);
	}

	float zVel = 0.0f;
	if (m_input.IsKeyDown(GLFW_KEY_E))
	{
		zVel = glm::radians(90.0f);
	}
	if (m_input.IsKeyDown(GLFW_KEY_Q))
	{
		zVel = glm::radians(-90.0f);
	}

	glm::quat velocityQuaternion = glm::quat(0.0f, glm::vec3(xVel, yVel, zVel));

	// hier geschiet die tatsächliche Rechnung des rotationsquaternions die du dir am besten nochmal anschaust
	m_orientationQuaternion += 0.5f * ((float)deltaTime) * velocityQuaternion * m_orientationQuaternion;
	m_orientationQuaternion = normalize(m_orientationQuaternion);
}