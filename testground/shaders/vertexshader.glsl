#version 430 core


layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColour;
layout(location = 2) in vec3 barycentricCoordinate;


layout(location = 3) uniform mat4 uModel;
layout(location = 4) uniform mat4 uView;
layout(location = 5) uniform mat4 uProjection;

out vec3 oColour;
out vec3 oBarycentricCoordinate;
 
void main(void)
{	
	gl_Position = vec4(vPosition, 0, 1) * uModel * uView * uProjection;
	
	oColour = vColour;
	oBarycentricCoordinate = barycentricCoordinate;
}