#version 430 core

in vec3 oColour;

out vec4 color;

uniform bool uOverrideEnabled;
uniform vec4 uOverrideColour;
 
void main(void)
{
	if(!uOverrideEnabled) {
		color = overrideColour;
	}
	else {
		color = oColour;
	}
}