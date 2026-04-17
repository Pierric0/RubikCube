#version 330

uniform mat3 transformation;

layout(location = 0) in vec3 position;

void main(){

	vec4 transient = transformation * vec4(position, 0.0);
	
	gl_Position = transformation * vec4(position, 1.0);

}