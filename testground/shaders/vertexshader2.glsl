#version 430 core


layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColour;


layout(location = 2) uniform mat4 uModel;

out vec3 oColour;
 
void main(void)
{	
	gl_Position = vec4(vPosition - vec2(0.4, 0.0), 0, 1) * uModel;
	
	oColour = vColour;
}