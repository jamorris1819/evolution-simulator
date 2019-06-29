#include "genotype.h"
#include "genemarker.h"
#include <iostream>
#include <vector>

Genotype::Genotype(bool fill)
{
	strandLength = (int)GeneMarker::GENE_COUNT;

	if (fill) {
		// Create some dummy genes.
		for (int i = 0; i < strandLength; i++) {
			strandA.push_back(new Gene<int>(i + 10, 0));
			strandB.push_back(new Gene<int>(i, 0));
		}
	}
}

Genotype::~Genotype()
{
	// Delete all genes from both strands.
	for (int i = 0; i < strandLength; i++) {
		delete strandA[i];
		delete strandB[i];
	}
}

Genotype* Genotype::clone()
{
	Genotype* clonedGenotype = new Genotype(false);

	// Clone the strands.

	for (int i = 0; i < strandLength; i++) {
		Base* gene = strandA[i];

		if (gene->typeInt) {
			clonedGenotype->strandA.push_back(((Gene<int>*)strandA[i])->clone());
			clonedGenotype->strandB.push_back(((Gene<int>*)strandB[i])->clone());
		}
		else if (gene->typeBool) {
			clonedGenotype->strandA.push_back(((Gene<bool>*)strandA[i])->clone());
			clonedGenotype->strandB.push_back(((Gene<bool>*)strandB[i])->clone());
		}
	}

	return clonedGenotype;
}