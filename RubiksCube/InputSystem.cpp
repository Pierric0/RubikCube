#include "InputSystem.h"
#include <GLFW/glfw3.h>

void InputSystem::Update()
{
	for (auto i = m_keyMapper.begin(); i != m_keyMapper.end(); ++i)
		i->second.Update();
}

void InputSystem::ObserveKey(int key)
{
	m_keyMapper[key] = KeyboardObserver(m_window, key);
}

bool InputSystem::IsLeftMouseButtonDown()
{
	return (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
}

bool InputSystem::IsRightMouseButtonDown()
{
	return (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
}

void InputSystem::GetPickingRay(const glm::mat4& transformationMatrix, glm::vec3& startingPoint, glm::vec3& direction)
{
	//absoluter pixelwert von x und y vom bildschirm (ursprung oben links)
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);

	//damit die positionen von der mitte des Bildschirms ist (Ursrpung jetzt mitte des Bildschirms)
	xpos = (xpos / screenWidth) * 2.0 - 1;
	ypos = 1 - 2 * (ypos / screenHeight);

	//start und endpunkt des strahls
	glm::vec4 nearPoint = glm::vec4((float)xpos, (float)ypos, 0.01f, 1.0f);
	glm::vec4 farPoint = nearPoint;
	farPoint.z = 0.99f;
	
	// diese Rechnungen müssen durchgeführt werden damit wir uns in die world-Space begeben
	glm::mat4 inverse = glm::inverse(transformationMatrix);
	nearPoint = inverse * nearPoint;
	farPoint = inverse * farPoint;

	// Damit es wieder einheitsvektoren? werden
	nearPoint /= nearPoint.w;
	farPoint /= farPoint.w;

	startingPoint = nearPoint;
	direction = farPoint - nearPoint;

	direction = glm::normalize(direction);
}

void InputSystem::GetMousePosition(double& xpos, double& ypos)
{
	glfwGetCursorPos(m_window, &xpos, &ypos);
}