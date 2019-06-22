#version 430 core

uniform mat4 uModel;
uniform mat4 uView;
//uniform mat4 uProjection;

in vec2 vPosition;
in vec3 vColour;

flat out vec3 oColour;
 
void main(void)
{	
	gl_Position = vec4(vPosition, 0, 1) * uModel;// * uProjection;

	oColour = vColour;
}