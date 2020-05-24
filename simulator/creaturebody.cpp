#include "creaturebody.h"
#include "contactlistener.h"
#include "FastNoise.h"

#define PI 3.14159265359

CreatureBody::CreatureBody(Genome* genome) : Body() {
	strideX = 1;
	strideY = 1;
	noiseType = 4;
	octaves = 1;
	length = 1.0f;
	width = 1.0f;
	frequency = 0.25f;

	steps = 30;
	offsetX = 0;
	offsetY = 0;
	r = 1;
	g = 0;
	b = 1;

	extractGenomeData(genome);
}

void CreatureBody::extractGenomeData(Genome* genome) {
	steps = genome->getGeneValue<int>(GeneMarker::GM_BODY_STEPS);
	offsetX = genome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETX);
	offsetY = genome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETY);
	r = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_R);
	g = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_G);
	b = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_B);
}

void CreatureBody::setNoiseOffset(float x, float y) {
	this->offsetX = x;
	this->offsetY = y;
}

void CreatureBody::setNoiseParams(int steps, int noiseType, int octaves) {
	this->steps = steps;
	this->noiseType = noiseType;
	this->octaves = octaves;
}

void CreatureBody::generate() {
	generateBodyPoints();
	generateMouth();
	generateEyes();
}

void CreatureBody::generateMouth() {
	/*b2Vec2 vert[4];

	// Assign shape's vertices.
	vert[0].Set(-0.2f, 1.2f);
	vert[1].Set(-0.2f, 0.0f);
	vert[2].Set(0.2f, 0.0f);
	vert[3].Set(0.2f, 1.2f);

	b2PolygonShape shape;
	shape.Set(vert, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 10.0f;
	fixtureDef.isSensor = true;
	fixtureDef.restitution = 0.6f;

	fixtureDef.filter.categoryBits = ContactType::MOUTH;

	physicsBody->CreateFixture(&fixtureDef);*/
}

void CreatureBody::generateBodyPoints() {
	FastNoise noise;
	noise.SetNoiseType(FastNoise::SimplexFractal);
	noise.SetFractalOctaves(octaves);
	noise.SetFrequency(frequency);
	int sides = steps;
	double step = PI / sides;


	// Basic creature generation.
	std::vector<eng::Vertex> vertices;
	eng::Vertex origin(glm::vec2(0, 0));

	// Generate half of the creature.
	for (int i = 0; i <= sides; i++) {
		eng::Vertex v(glm::sin(i * step), glm::cos(i * step));
		float size = (noise.GetNoise((i * strideX) + offsetX, (i * strideY) + offsetY) + 1) / 2.0f;
		v.multiply(size);
		vertices.push_back(v);
	}

	// Copy and flip the vertices so they're mirrored.
	int size = vertices.size();
	for (int i = 1; i < size; i++) {
		eng::Vertex v = vertices[size - i - 1];
		v.setPosition(glm::vec2(-1.0f, 1.0f) * v.getPosition());
		vertices.push_back(v);
	}

	// Scale body width length/width.
	for (int i = 0; i < vertices.size(); i++) {
		eng::Vertex v = vertices[i];
		v.setPosition(glm::vec2(-width, length) * v.getPosition());
		v.setColour(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
		vertices[i] = v;
	}

	// Add origin to start so can be rendered as polygon
	origin.setColour(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
	vertices.insert(vertices.begin(), origin);

	// Assign these vertices to the polygon model.
	eng::Polygon mainBody;
	mainBody.setVertices(vertices);
	primaryBody = mainBody;
}

void CreatureBody::generateEyes() {
	steps = 30;
	double step = 2.0 * PI / steps;

	// Basic creature generation.
	std::vector<eng::Vertex> vertices;

	// Generate the eye.
	for (int i = 0; i < steps; i++) {
		eng::Vertex v(glm::sin(i * step), glm::cos(i * step));
		v.multiply(0.15f);
		v.setPosition(v.getPosition() + glm::vec2(-0.3f, 0.35f));
		v.setColour(glm::vec3(1, 1, 1));
		vertices.push_back(v);
	}

	eng::Polygon eye;
	eye.setVertices(vertices);
	secondaryBodies.push_back(eye);

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setPosition(vertices[i].getPosition() - glm::vec2(-0.3f, 0.35f));
		vertices[i].setPosition((vertices[i].getPosition() * 0.35f) + glm::vec2(0, 0.05f));
		vertices[i].setPosition(vertices[i].getPosition() + glm::vec2(-0.3f, 0.35f));
		vertices[i].setColour(glm::vec3(0, 0, 0));
	}

	eye.setVertices(vertices);
	secondaryBodies.push_back(eye);

	/*vertices.clear();

	// Generate the eye.
	for (int i = 0; i < steps; i++) {
		eng::Vertex v(glm::sin(i * step), glm::cos(i * step));
		v.multiply(0.15f);
		v.setPosition(v.getPosition() + glm::vec2(0.3f, 0.35f));
		v.setColour(glm::vec3(1, 1, 1));
		vertices.push_back(v);
	}

	// Assign these vertices to the polygon model.
	p = new VertexRenderer(shaderID);
	p->setVertices(vertices);
	p->load();
	polygons.push_back(p);

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setPosition(vertices[i].getPosition() - glm::vec2(0.3f, 0.35f));
		vertices[i].setPosition((vertices[i].getPosition() * 0.35f) + glm::vec2(0, 0.05f));
		vertices[i].setPosition(vertices[i].getPosition() + glm::vec2(0.3f, 0.35f));
		vertices[i].setColour(glm::vec3(0, 0, 0));
	}
	p = new VertexRenderer(shaderID);
	p->setVertices(vertices);
	p->load();
	polygons.push_back(p);*/
}

/*void CreatureBody::generatePhysicsBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	physicsBody = world->CreateBody(&bodyDef);

	// Create the triangles for this body.
	for (int i = 0; i < vertices.size() - 1; i++) {
		// Get vertices.
		eng::Vertex v1 = vertices[i];
		eng::Vertex v2 = vertices[i + 1];
		b2Vec2 vert[3];

		// Assign shape's vertices.
		vert[0].Set(v1.getPosition().x, v1.getPosition().y);
		vert[1].Set(0.0f, 0.0f);
		vert[2].Set(v2.getPosition().x, v2.getPosition().y);

		b2PolygonShape shape;
		shape.Set(vert, 3);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 10.0f;
		fixtureDef.restitution = 0.6f;

		fixtureDef.filter.categoryBits = ContactType::CREATURE;

		physicsBody->CreateFixture(&fixtureDef);
	}

	// Apply some settings to the new body.
	physicsBody->SetLinearDamping(20.0f);
	physicsBody->SetAngularDamping(20.0f);
}*/