#include "genome.h"
#include "genemarker.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"
#include <thread>

Genome::Genome(bool fill)
{
	strandLength = 0;
	strandWeights = nullptr;
}

Genome::~Genome()
{
	// Delete all genes from both strands.
	for (int i = 0; i < strandLength; i++) {
		delete strandA[i];
		delete strandB[i];
	}
	delete[] strandWeights;
}

int Genome::generateInt(int startingArea, int maxSpread, int minStride, int maxStride, int* spread)
{
	int chosenPoint = (startingArea - maxSpread) + (rand() % (2 * maxSpread));

	int spreadDivisor = glm::max(1, maxStride - minStride);
	*spread = minStride + (rand() % spreadDivisor);

	return chosenPoint;
}

void Genome::generateCreature()
{
	// Create generic genome.

	// SIZE
	int* spread = new int;
	int position = generateInt(50, 20, 10, 30, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_SIZE));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_SIZE));

	// COLOUR R
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_R));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_R));

	// COLOUR G
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_G));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_G));

	// COLOUR B
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_B));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_B));

	// SPEED MOVEMENT
	position = generateInt(20, 10, 5, 15, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_SPEED_MOVEMENT));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_SPEED_MOVEMENT));

	// SPEED ROTATION
	position = generateInt(15, 5, 5, 10, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_SPEED_ROTATION));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_SPEED_ROTATION));

	// BODY STEPS
	position = generateInt(10, 2, 0, 2, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_BODY_STEPS));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_BODY_STEPS));

	// BODY MUTATION RATE
	position = generateInt(15, 5, 5, 10, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_BODY_MUTATION_RATE));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_BODY_MUTATION_RATE));

	// BODY OFFSET X
	position = generateInt(0, 5000, 0, 1, spread);
	strandA.push_back(new Gene<float>(position - *spread, (int)GeneMarker::GM_BODY_OFFSETX));
	strandB.push_back(new Gene<float>(position + *spread, (int)GeneMarker::GM_BODY_OFFSETX));

	// BODY OFFSET Y
	position = generateInt(0, 5000, 0, 1, spread);
	strandA.push_back(new Gene<float>(position - *spread, (int)GeneMarker::GM_BODY_OFFSETY));
	strandB.push_back(new Gene<float>(position + *spread, (int)GeneMarker::GM_BODY_OFFSETY));
	delete spread;

	strandLength = strandA.size();
	strandWeights = new double[strandLength];

	// Initialise weights.
	for (int i = 0; i < strandLength; i++) {
		strandWeights[i] = (rand() % 100) / 100.0;
	}
}

void Genome::generatePlant()
{
	// Create generic genome.
	// COLOUR R
	int* spread = new int;
	int position = generateInt(4, 4, 2, 4, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_R));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_R));

	// COLOUR G
	position = generateInt(102, 4, 2, 4, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_G));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_G));

	// COLOUR B
	position = generateInt(35, 4, 2, 4, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_COLOUR_B));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_COLOUR_B));

	// LEAF LENGTH
	position = generateInt(500, 500, 20, 50, spread);
	strandA.push_back(new Gene<float>((position - *spread) / 500.0f, (int)GeneMarker::GM_LEAF_LENGTH));
	strandB.push_back(new Gene<float>((position + *spread) / 500.0f, (int)GeneMarker::GM_LEAF_LENGTH));

	// LEAF LAYERS
	position = generateInt(3, 2, 1, 1, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_LEAF_LAYERS));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_LEAF_LAYERS));

	// BUSH COUNT
	position = generateInt(5, 2, 1, 1, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_BUSH_COUNT));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_BUSH_COUNT));
	
	// BODY SIZE
	position = generateInt(75, 50, 4, 8, spread);
	strandA.push_back(new Gene<float>((position - *spread) / 100.0f, (int)GeneMarker::GM_SIZE));
	strandB.push_back(new Gene<float>((position + *spread) / 100.0f, (int)GeneMarker::GM_SIZE));

	// BODY MUTATION RATE
	position = generateInt(15, 5, 5, 10, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_BODY_MUTATION_RATE));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_BODY_MUTATION_RATE));

	// BODY MUTATION RATE
	position = generateInt(24, 4, 2, 4, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_LEAF_STEPS));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_LEAF_STEPS));
	delete spread;

	strandLength = strandA.size();
	strandWeights = new double[strandLength];

	// Initialise weights.
	for (int i = 0; i < strandLength; i++) {
		strandWeights[i] = (rand() % 100) / 100.0;
	}
}

Genome* Genome::clone()
{
	Genome* clonedGenome = new Genome(false);

	// Clone the strands.

	for (int i = 0; i < strandLength; i++) {
		Base* gene = strandA[i];

		if (gene->typeInt) {
			clonedGenome->strandA.push_back(((Gene<int>*)strandA[i])->clone());
			clonedGenome->strandB.push_back(((Gene<int>*)strandB[i])->clone());
		}
		else if (gene->typeBool) {
			clonedGenome->strandA.push_back(((Gene<bool>*)strandA[i])->clone());
			clonedGenome->strandB.push_back(((Gene<bool>*)strandB[i])->clone());
		}
		else if (gene->typeFloat) {
			clonedGenome->strandA.push_back(((Gene<float>*)strandA[i])->clone());
			clonedGenome->strandB.push_back(((Gene<float>*)strandB[i])->clone());
		}
		else {
			std::cerr << "Unknown type - could not be cloned" << std::endl;
		}
	}

	clonedGenome->strandLength = clonedGenome->strandA.size();

	return clonedGenome;
}

void Genome::mutate()
{
	for (int i = 0; i < strandLength; i++) {
		if (rand() % 10 == 0) {
			Base* base = strandA[i];
			if (base->typeInt) {
				((Gene<int>*)base)->mutate();
			}
			else if (base->typeBool) {
				((Gene<bool>*)base)->mutate();
			}
			else if (base->typeFloat) {
				((Gene<float>*)base)->mutate();
			}
			else {
				std::cerr << "Gene could not be mutated as it is an unknown type" << std::endl;
			}
		}

		if (rand() % 10 == 0) {
			Base* base = strandB[i];
			if (base->typeInt) {
				((Gene<int>*)base)->mutate();
			}
			else if (base->typeBool) {
				((Gene<bool>*)base)->mutate();
			}
			else if (base->typeFloat) {
				((Gene<float>*)base)->mutate();
			}
			else {
				std::cerr << "Gene could not be mutated as it is an unknown type" << std::endl;
			}
		}
	}
}

Genome* Genome::cross(Genome* genome1, Genome* genome2)
{
	if (genome1->strandLength != genome2->strandLength) return nullptr;

	Genome* childGenome = new Genome(false);
	bool flipStrands = rand() % 2 == 0;
	Genome* parentA = flipStrands ? genome1 : genome2;
	Genome* parentB = !flipStrands ? genome1 : genome2;

	std::vector<Base*> strandA;
	std::vector<Base*> strandB;

	childGenome->strandLength = genome1->strandLength;
	childGenome->strandWeights = new double[genome1->strandLength];
	for (int i = 0; i < genome1->strandLength; i++) {
		strandA.push_back(parentA->strandA[i]->clone());
		strandB.push_back(parentB->strandB[i]->clone());
		childGenome->strandWeights[i] = rand() % 2 == 0 ? genome1->strandWeights[i] : genome2->strandWeights[i];
	}

	childGenome->strandA = strandA;
	childGenome->strandB = strandB;
	
	return childGenome;
}
