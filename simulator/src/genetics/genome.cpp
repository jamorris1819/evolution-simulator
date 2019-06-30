#include "genome.h"
#include "genemarker.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"

Genome::Genome(bool fill)
{
	strandLength = (int)GeneMarker::GENE_COUNT;
	strandWeights = new double[strandLength];
	srand(time(NULL));
	if (fill) {
		generate();
	}
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
	*spread = minStride + (rand() % (maxStride - minStride));

	return chosenPoint;
}

void Genome::generate()
{
	// Initialise weights.
	for (int i = 0; i < strandLength; i++) {
		strandWeights[i] = (rand() % 100) / 100.0;
	}

	srand(time(NULL));
	
	// Create generic genome.

	// SIZE
	int* spread = new int;
	int position = generateInt(50, 20, 10, 30, spread);
	strandA.push_back(new Gene<int>(position - *spread, (int)GeneMarker::GM_SIZE));
	strandB.push_back(new Gene<int>(position + *spread, (int)GeneMarker::GM_SIZE));
	delete spread;

	Gene<int>* a = (Gene<int>*)strandA[0];

	// COLOUR R
	spread = new int;
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(glm::clamp(position - *spread, 0, 255), (int)GeneMarker::GM_COLOUR_R));
	strandB.push_back(new Gene<int>(glm::clamp(position + *spread, 0, 255), (int)GeneMarker::GM_COLOUR_R));
	delete spread;

	// COLOUR G
	spread = new int;
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(glm::clamp(position - *spread, 0, 255), (int)GeneMarker::GM_COLOUR_G));
	strandB.push_back(new Gene<int>(glm::clamp(position + *spread, 0, 255), (int)GeneMarker::GM_COLOUR_G));
	delete spread;

	// COLOUR B
	spread = new int;
	position = generateInt(127, 100, 30, 80, spread);
	strandA.push_back(new Gene<int>(glm::clamp(position - *spread, 0, 255), (int)GeneMarker::GM_COLOUR_B));
	strandB.push_back(new Gene<int>(glm::clamp(position + *spread, 0, 255), (int)GeneMarker::GM_COLOUR_B));
	delete spread;

	// SPEED MOVEMENT
	spread = new int;
	position = generateInt(20, 10, 5, 15, spread);
	strandA.push_back(new Gene<int>(glm::clamp(position - *spread, 0, 255), (int)GeneMarker::GM_SPEED_MOVEMENT));
	strandB.push_back(new Gene<int>(glm::clamp(position + *spread, 0, 255), (int)GeneMarker::GM_SPEED_MOVEMENT));
	delete spread;

	// SPEED MOVEMENT
	spread = new int;
	position = generateInt(15, 5, 5, 10, spread);
	strandA.push_back(new Gene<int>(glm::clamp(position - *spread, 0, 255), (int)GeneMarker::GM_SPEED_ROTATION));
	strandB.push_back(new Gene<int>(glm::clamp(position + *spread, 0, 255), (int)GeneMarker::GM_SPEED_ROTATION));
	delete spread;


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
	}

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
		}

		if (rand() % 10 == 0) {
			Base* base = strandB[i];
			if (base->typeInt) {
				((Gene<int>*)base)->mutate();
			}
			else if (base->typeBool) {
				((Gene<bool>*)base)->mutate();
			}
		}
	}
}