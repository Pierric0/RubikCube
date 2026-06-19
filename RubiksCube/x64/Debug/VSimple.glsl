#version 330

uniform mat4 transformation; // transformationsmatrix (uniform so wie static bei klassen. gillt für alle gleich)

layout(location = 0) in vec3 position; // index 0; in bedeutet inhalt kommt von außen

void main()
{
	gl_Position = transformation * vec4(position, 1.0f);
}