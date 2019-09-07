#include "base.h"
#include <iostream>

Base::Base() {}
Base* Base::clone()
{
	Base* base = new Base();
	base->dominant = dominant;
	base->enabled = enabled;
	base->order = order;
	base->typeBool = typeBool;
	base->typeInt = typeInt;
	base->typeFloat = typeFloat;

	return base;
}