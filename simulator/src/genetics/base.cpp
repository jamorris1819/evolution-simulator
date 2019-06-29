#include "base.h"
#include <iostream>

Base::Base() {}
Base* Base::clone()
{
	std::cout << "a" << std::endl;
	return this;
}