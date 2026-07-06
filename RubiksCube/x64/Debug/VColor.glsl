#version 330

uniform mat4 transformation; // transformationsmatrix (uniform so wie static bei klassen. gillt für alle gleich)

layout(location = 0) in vec3 position; // index 0; in bedeutet inhalt kommt von außen
layout(location = 1) in vec3 inColor;

out vec3 vertColor; // gehe mal davon aus das out bedeutet das der inhalt rausgegeben wird

void main()
{
	gl_Position = transformation * vec4(position, 1.0f);
	vertColor = inColor;
}