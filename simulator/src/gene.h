#pragma once

#include "genemarker.h"
#include "base.h"
#include <ctime>
#include "glm\glm.hpp"

template<class T>
class Gene : public Base
{
public:
	Gene(T value, int order);
	Gene(T value, GeneMarker marker);
	~Gene();
	void setValue(T nvalue);
	void enable();
	void disable();
	void setDominant(bool dominant);
	bool getDominant();
	Gene<T>* clone();
	void mutate();
	T getValue();
private:
	T value;
	T upperLimit;
	T lowerLimit;
};

template<class T> Gene<T>::Gene(T value, int order)
{

	dominant =  (int)(rand() % 4) != 0;	// 1 in 4 change of being false.
	enabled = true;
	this->order = order;

	typeInt = std::is_same_v<T, int>;
	typeBool = std::is_same_v<T, bool>;
	typeFloat = std::is_same_v<T, float>;

	std::tuple<int, int> limits = geneMarkerLimits((GeneMarker)order);
	lowerLimit = std::get<0>(limits);
	upperLimit = std::get<1>(limits);

	setValue(value);
}

template<class T> Gene<T>::Gene(T value, GeneMarker marker) : Gene<T>(value, (int)marker) { }

template<class T> Gene<T>::~Gene()
{
	std::cout << "gene destroyed" << std::endl;
}

template<class T> void Gene<T>::setValue(T nvalue)
{
	T newVal = nvalue;
	if (upperLimit > lowerLimit) newVal = glm::clamp(newVal, lowerLimit, upperLimit);
	this->value = newVal;
}

template<class T> T Gene<T>::getValue()
{
	return value;
}

template<class T> void Gene<T>::enable()
{
	enabled = true;
}

template<class T> void Gene<T>::disable()
{
	enabled = false;
}

template<class T> void Gene<T>::setDominant(bool dominant)
{
	this->dominant = dominant;
}

template<class T> bool Gene<T>::getDominant()
{
	return dominant;
}

template<class T> Gene<T>* Gene<T>::clone()
{
	Gene<T>* clone = new Gene<T>(value, order);
	clone->setDominant(dominant);
	clone->enabled = enabled;

	return clone;
}

template<class T> void Gene<T>::mutate()
{
	// TODO: refactor
	if (typeInt) {
		/*
			Types of mutation:	- Toggle gene dominance
								- Value change
									- Minor change
									- Major change
		*/
		int total = 25;
		int mutationChance[3] = {
			5,
			20,
		};

		int number = rand() % total;
		if (number < mutationChance[0]) {
			// Toggle gene dominance.
			setDominant(!getDominant());
		}
		else if (number < mutationChance[0] + mutationChance[1]) {
			// We need to change a value.
			number = rand() % 10;
			std::tuple<int, int> limits = geneMarkerLimits((GeneMarker)order);
			if (lowerLimit < upperLimit) {
				float range = upperLimit - lowerLimit;
				if (number < 1) {
					// Major change
					range /= 10.0f;
				}
				else {	
					// Minor change
					range /= 40.0f;
				}
				number = rand() % 2 == 0 ? range : -range;
				setValue(getValue() + number);
			}
			else {
				float fNumber;
				int changeAmount;
				if (number < 1) {
					// Major change
					changeAmount = 100;
				}
				else {
					// Minor change
					changeAmount = 30;
				}
				number = rand() % changeAmount;
				number -= changeAmount / 2;
				fNumber = 1.0f + ((float)number / (float)changeAmount);
				setValue((int)(glm::floor(value * fNumber)));
			}
		}
	}
	else if (typeBool) {
		int total = 25;
		int mutationChance[3] = {
			5,
			20,
		};

		int number = rand() % total;
		if (number < mutationChance[0]) {
			// Toggle gene dominance.
			setDominant(!getDominant());
		}
		else if (number < mutationChance[0] + mutationChance[1]) {
			// We need to flip the value.
			value = !value;
		}
	}
	else if (typeFloat) {
		/*
		Types of mutation:	- Toggle gene dominance
		- Value change
		- Minor change
		- Major change
		*/
		int total = 25;
		int mutationChance[3] = {
			5,
			20,
		};

		int number = rand() % total;
		if (number < mutationChance[0]) {
			// Toggle gene dominance.
			setDominant(!getDominant());
		}
		else if (number < mutationChance[0] + mutationChance[1]) {
			// We need to change a value.
			number = rand() % 10;
			float fNumber;
			int changeAmount;
			if (number < 3) {
				// Major change
				changeAmount = 100;
			}
			else {
				// Minor change
				changeAmount = 30;
			}
			number = rand() % changeAmount;
			number -= changeAmount / 2;
			fNumber = 1.0f + ((float)number / (float)changeAmount);
			setValue(value + 0.025f);
		}
	}
	else {
		std::cerr << "Gene could not be mutated as it is an unknown type" << std::endl;
	}
}