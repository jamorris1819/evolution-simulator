#version 430 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

in vec2 vPosition;
in vec3 vColour;

flat out vec3 oColour;
 
void main(void)
{	
	oColour = vColour;
	gl_Position = vec4(vPosition, 1, 1) * uModel * uView * uProjection;

	oColour = vColour;
}