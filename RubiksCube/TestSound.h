#pragma once
#include "GameInterface.h"
#include "InputSystem.h"

class TestSound : public GameInterface
{
public:
	virtual void Initialize(GLFWwindow* window);
	virtual void Update(double deltaTime);

private:
	InputSystem m_input;
};

