#pragma once
#include "rectangle.h"

namespace engine {
	class Square : public Rectangle {
	public:
		Square(int s) : Rectangle(s, s) {}
	};
}