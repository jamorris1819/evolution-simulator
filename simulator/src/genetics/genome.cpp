#include "genome.h"
#include "genemarker.h"
#include <iostream>
#include <vector>

Genome::Genome(bool fill)
{
	strandLength = (int)GeneMarker::GENE_COUNT;

	if (fill) {
		// Create some dummy genes.
		for (int i = 0; i < strandLength; i++) {
			if (i % 2 == 0) {
				strandA.push_back(new Gene<int>(i + 10, i));
				strandB.push_back(new Gene<int>(i, i));
			}
			else {
				strandA.push_back(new Gene<bool>(false, i));
				strandB.push_back(new Gene<bool>(false, i));
			}
		}
	}
}

Genome::~Genome()
{
	// Delete all genes from both strands.
	for (int i = 0; i < strandLength; i++) {
		delete strandA[i];
		delete strandB[i];
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
	}

	return clonedGenome;
}