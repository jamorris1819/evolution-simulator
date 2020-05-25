#version 430 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

in vec2 vPosition;
in vec3 vColour;
in vec2 vOffset;
in vec3 vOverrideColour;

out vec3 oColour;
 
void main(void)
{	
	gl_Position = vec4(vPosition + vOffset, 0, 1) * uModel * uView * uProjection;

	bool override = vOverrideColour != vec3(1, 1, 1);
	
	oColour = override ? vOverrideColour : vColour;
}