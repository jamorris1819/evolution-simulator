#pragma once
template<class T>
class Gene
{
public:
	Gene(T value, int order);
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
	bool dominant;
	bool enabled;
	int order;
};

template<class T> Gene<T>::Gene(T value, int order)
{
	setValue(value);

	dominant = true;
	enabled = true;
	this->order = order;
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

	return clone;
}