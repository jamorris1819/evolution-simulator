#pragma once
#include "cameraevent.h"

namespace engine {
	class CameraMoveEvent : public CameraEvent {
	public:
		CameraMoveEvent(double x, double y) : dx(x), dy(y) {}
		double dx;
		double dy;
	};
}