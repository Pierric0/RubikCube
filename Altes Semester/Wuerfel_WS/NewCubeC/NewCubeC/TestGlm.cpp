#include "TestGlm.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

void TestGlm::Initialize() {
	
	/*glm::vec3 firstVec(1.0f, -1.0f, 0.0f);
	glm::vec3 secondVec(-1.0f, -1.0f, 0.0f);

	float innerProduct = glm::dot(firstVec, secondVec)/(glm::length(firstVec) * glm::length(secondVec));

	float innerAngle = glm::degrees(glm::acos(innerProduct));

	glm::vec3 cross = glm::cross(firstVec, secondVec);

	float secondAngle = glm::degrees(glm::asin(glm::length(cross) / (glm::length(firstVec)*glm::length(secondVec))));*/

	/*glm::mat4 test = glm::mat4(1.0f);
	glm::mat4 second = glm::rotate(test, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 third = glm::translate(test, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 combo = second * third;

	glm::mat4 look = glm::lookAt(glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));

	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

	glm::mat4 totalMat = perspective * look * combo;*/

	m_orientationQuaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void TestGlm::Update(double deltaTime) {
	//hack für debuggen
	deltaTime = 0.02;
	

	glm::quat rotVelocity = glm::quat(0.0, glm::radians(189.0f),0.0,0.0);

	glm::quat time_derivative = 0.5f * rotVelocity * m_orientationQuaternion;

	m_orientationQuaternion += static_cast<float>(deltaTime) * time_derivative;

	m_orientationQuaternion = glm::normalize(m_orientationQuaternion);

	glm::mat4 rotationMatrix = glm::mat4_cast(m_orientationQuaternion);
}
