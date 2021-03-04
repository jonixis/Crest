#pragma once

#include "Camera.h"

class FlightCamera : public Camera {

 public:
	using Camera::Camera;

	void update() override;

 private:

};
