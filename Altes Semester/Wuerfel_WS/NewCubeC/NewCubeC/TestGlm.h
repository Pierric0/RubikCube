#pragma once
#include <glm/ext/quaternion_float.hpp>

#include "GameInterface.h"

class TestGlm : public GameInterface {

public: 
	virtual void Initialize();

	virtual void Update(double deltaTime);

private:
	glm::quat m_orientationQuaternion;
};