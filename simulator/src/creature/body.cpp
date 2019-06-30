#include "body.h"
#include "noise\FastNoise.h"
#include "GL\glew.h"
#include "glm\glm.hpp"

#define PI 3.14159265359

Body::Body(GLuint shader) : PolygonR(shader)
{
	seed = 0;
	strideX = 1;
	strideY = 1;
	offsetX = 0;
	offsetY = 0;
	length = 1.0f;
	width = 1.0f;
	frequency = 0.25f;
}

Body::~Body()
{

}

void Body::addParameters(int steps, int noiseType, int octaves, float offsetX, float offsetY, int r, int g, int b)
{
	this->steps = steps;
	this->noiseType = noiseType;
	this->octaves = octaves;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->r = r;
	this->g = g;
	this->b = b;
}

void Body::generate()
{
	FastNoise noise;
	noise.SetSeed(seed);
	noise.SetNoiseType(FastNoise::SimplexFractal);
	noise.SetFractalOctaves(octaves);
	noise.SetFrequency(frequency);
	int sides = steps;
	double step = PI / sides;

	// Basic creature generation.
	vector<Vertex> vertices;

	// Generate half of the creature.
	for (int i = 0; i <= sides; i++) {
		Vertex v(glm::sin(i * step), glm::cos(i * step));
		float size = (noise.GetNoise((i * strideX) + offsetX, (i * strideY) + offsetY) + 1) / 2.0f;
		v.multiply(80.0f);
		v.multiply(size);
		vertices.push_back(v);
	}

	// Copy and flip the vertices so they're mirrored.
	int size = vertices.size();
	for (int i = 0; i < size; i++) {
		Vertex v = vertices[size - i - 1];
		v.setPosition(glm::vec2(-1.0f, 1.0f) * v.getPosition());
		vertices.push_back(v);
	}
	//offsetX += 0.01f;
	//offsetY += 0.01f;

	// Scale body width length/width.

	for (int i = 0; i < vertices.size(); i++) {
		Vertex v = vertices[i];
		v.setPosition(glm::vec2(-width, length) * v.getPosition());
		v.setColour(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
		vertices[i] = v;
	}

	setVertices(vertices);
}