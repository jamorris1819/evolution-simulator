#pragma once
#define e 2.71828
#include "glm\common.hpp"

class Function {
public:
	static double sigmoid(double x);
	static double relu(double x);
};

// Performs the sigmoid function.
double Function::sigmoid(double x) {
	return (1 / (1 + pow(e, -x)));
}

// Performs the RELU function.
double Function::relu(double x) {
	return glm::clamp(x, 0.0, 1.0);
}