#include <vector>

#include "CubieRenderer.h"
#include "ShaderUtil.h"
#include <glm/gtc/type_ptr.hpp>

void CubieRenderer::Initialize() {

	std::vector<glm::vec3> positionField;
	std::vector<glm::vec3> colorField;
	float floatArray[6 * 6 *3];

}

void CubieRenderer::TranscirbeToFloatArray(std::vector<glm::vec3>& vecArray, float* floatArray) {
	
	int writingCounter = 0;

	for (int vert = 0; vert < 36; ++vert) {
		for (int coord = 0; coord < 3; ++coord) {
			floatArray[writingCounter++] = vecArray[vert][coord];
		}
	}

}
