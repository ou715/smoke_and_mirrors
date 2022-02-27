#include "camera.h"

Camera::Camera() : cameraLocation{ Vector3() }, up{ Vector3(0, 1, 0) }, viewingDirection{ Vector3(0, 0, -1) }, horizontal{ 2 }, vertical{ 2 }{}
Camera::Camera(Vector3 location, Vector3 up, Vector3 viewingDirection, float horizontal, float vertical) :
	cameraLocation{ location }
	, up{ up }
	, viewingDirection{ viewingDirection }
	, horizontal{ horizontal }
	, vertical{ vertical } {}