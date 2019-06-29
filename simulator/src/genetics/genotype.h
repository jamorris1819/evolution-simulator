#pragma once
#include "base.h"
#include "gene.h"
#include "genemarker.h"
#include <vector>

class Genotype
{
public:
	Genotype(bool fill);
	~Genotype();
	Genotype* clone();
	template<class T> Gene<T>* getGene(int order, bool mainStrand);
	template<class T> Gene<T>* getGene(GeneMarker marker, bool mainStrand);
	std::vector<Base*> strandA;
	std::vector<Base*> strandB;
	int strandLength;
};

template<class T> Gene<T>* Genotype::getGene(int order, bool mainStrand)
{
	std::vector<Base*> strandToUse = strand == 0 ? strandA : strandB;
	Base* gene = strandToUse[order];
	return ((Gene<T>*)gene);
}

template<class T> Gene<T>* Genotype::getGene(GeneMarker marker, bool mainStrand)
{
	return getGene<T>((int)marker, strand);
}