#version 430 core


layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColour;
layout(location = 2) in vec3 barycentricCoordinate;
layout(location = 3) in vec3 colour1;
layout(location = 4) in vec3 colour2;


uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 oColour;
out vec3 oBarycentricCoordinate;
out vec2 oPosition;

out vec3 colourA;
out vec3 colourB;
out vec3 colourC;
 
void main(void)
{	
	gl_Position = vec4(vPosition, 0, 1) * uModel * uView * uProjection;
	oPosition = vPosition;
	oColour = vColour;
	oBarycentricCoordinate = barycentricCoordinate;

	colourA = oColour;
	colourB = colour1;
	colourC = colour2;
}