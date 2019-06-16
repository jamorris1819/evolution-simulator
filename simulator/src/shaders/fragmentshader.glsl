#version 430 core

flat in vec3 oColour;

out vec4 color;
 
void main(void)
{
	color = vec4(oColour, 1);
}