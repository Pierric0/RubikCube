#include "TestKey.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void TestKey::Initialize(GLFWwindow* window)
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
	m_orientationQuaternion = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void TestKey::Render(float aspectRatio)
{
	// Hier wird die tatsächliche perspektive ausgerechnet. das letzte (m_orientationQuaternion) ist die tatsächliche rotation. Schau dir alle hier am besten nochmal an
	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) *
		glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::mat4_cast(m_orientationQuaternion);

	m_cubieRenderer.Render(globalTransformation);
}

void TestKey::ClearResources()
{
	m_cubieRenderer.ClearResources();
}

void TestKey::Update(double deltaTime)
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