#pragma once

#include "genemarker.h"
#include "base.h"
#include <ctime>

template<class T>
class Gene : public Base
{
public:
	Gene(T value, int order);
	Gene(T value, GeneMarker marker);
	~Gene();
	void setValue(T value);
	void enable();
	void disable();
	void setDominant(bool dominant);
	bool getDominant();
	Gene<T>* clone();
	T getValue();
private:
	T value;
};

template<class T> Gene<T>::Gene(T value, int order)
{
	setValue(value);

	dominant =  (int)(rand() % 4) != 0;	// 1 in 4 change of being false.
	enabled = true;
	this->order = order;

	typeInt = std::is_same_v<T, int>;
	typeBool = std::is_same_v<T, bool>;
}

template<class T> Gene<T>::Gene(T value, GeneMarker marker)
{
	Gene(value, (int)marker);
}

template<class T> Gene<T>::~Gene()
{
}

template<class T> void Gene<T>::setValue(T value)
{
	this->value = value;
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

	std::cout << "b" << std::endl;
	return clone;
}