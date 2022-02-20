#pragma once

#include "geometry.h"


class Camera {
public:
	Vector3 cameraLocation;
	Vector3 up;
	Vector3 viewingDirection; //Also the normal of the viewport for now
	float horizontal;
	float vertical;
	Vector3 upperLeftCorner = Vector3(-horizontal / 2, vertical / 2, viewingDirection.z); // change to viewport normal in the future
	//The plane containing up and right will be

	Camera();
	Camera(Vector3 location, Vector3 up, Vector3 viewingDirection, float horizontal, float vertical);
};