#pragma once
#include <glm/mat4x4.hpp>

class CubieRenderer
{
public:
	void Initialize();
	void Render(const glm::mat4& transformationMatrix);
	void ClearResources();

	float GetCubieExtension() const { return 2.0f * m_offset; }


private:
	
	const float m_offset = 0.5f;

	void TranscirbeToFloatArray(std::vector<glm::vec3>& vecArray, float* floatArray);
};