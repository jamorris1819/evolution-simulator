#pragma once
#include "base.h"
#include "gene.h"
#include "genemarker.h"
#include <vector>

class Genome {
public:
	Genome(bool fill);
	~Genome();
	Genome* clone();
	void generateCreature();
	void generatePlant();
	void mutate();
	static Genome* cross(Genome* genome1, Genome* genome2);
	int generateInt(int startingArea, int maxSpread, int minStride, int maxStride, int* spread);
	int generateFloat(int startingArea, int maxSpread, int minStride, int maxStride, int* spread);
	template<class T> Gene<T>* getGene(int order, bool mainStrand) const;
	template<class T> T getGeneValueInt(int order) const;
	template<class T> T getGeneValue(GeneMarker marker) const;
	std::vector<Base*> strandA;
	std::vector<Base*> strandB;
	double* strandWeights;
	int strandLength;
};

template<class T> Gene<T>* Genome::getGene(int order, bool mainStrand) const {
	std::vector<Base*> strandToUse = mainStrand ? strandA : strandB;
	Base* gene = nullptr;
	for (int i = 0; i < strandToUse.size(); i++) {
		if (strandToUse[i]->order == order) {
			gene = strandToUse[i];
			break;
		}
	}

	if (gene == nullptr) {
		std::cout << "No gene was found" << std::endl;
		return nullptr;
	}

	return ((Gene<T>*)gene);
}

template<class T> T Genome::getGeneValueInt(int order) const {
	T value = 0;

	Gene<T>* geneA = getGene<T>(order, true);
	Gene<T>* geneB = getGene<T>(order, false);

	if (geneA == nullptr || geneB == nullptr) {
		std::cout << "nullptr on gene" << std::endl;
	}

	bool domA = geneA->getDominant();
	bool domB = geneB->getDominant();

	int index = -1;
	for (int i = 0; i < strandA.size(); i++) {
		if (order == strandA[i]->order) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		std::cout << "Gene couldn't be found..." << std::endl;
		abort();
	}

	float weight = strandWeights[index]; // TODO: this may be the problem.

	// If this is an integer, calculate a new int based on the weights.
	if (std::is_same_v<T, int>) {
		int valA = geneA->getValue();
		int valB = geneB->getValue();

		// If one gene is dominant over the other, take that value.
		if (domA && !domB) value = valA;
		else if (!domA && domB) value = valB;
		else {
			// If both genes are either dominant OR recessive.
			// Use weight to determine final value.
			int delta = valB - valA;
			value = valA + weight * delta;
		}
	}
	// If this is a bool, determine what bool is returned.
	else if (std::is_same_v<T, bool>) {
		bool valA = geneA->getValue();
		bool valB = geneB->getValue();

		// If one gene is dominant over the other, take that value.
		if (domA && !domB) value = valA;
		else if (!domA && domB) value = valB;
		else {
			// If both genes are either dominant OR recessive.
			// Use weight to determine which value is returned.
			value = weight > 0.5 ? valA : valB;
		}
	}
	else if (std::is_same_v<T, float>) {
		float valA = geneA->getValue();
		float valB = geneB->getValue();

		// If one gene is dominant over the other, take that value.
		if (domA && !domB) value = valA;
		else if (!domA && domB) value = valB;
		else {
			// If both genes are either dominant OR recessive.
			// Use weight to determine final value.
			float delta = valB - valA;
			value = valA + weight * delta;
		}
	}
	else {
		std::cerr << "Gene could not be mutated as it is an unknown type" << std::endl;
	}

	return value;
}

template<class T> T Genome::getGeneValue(GeneMarker marker) const {
	return getGeneValueInt<T>((int)marker);
}
