#pragma once


struct PPM {
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
};


PPM transpose(PPM image, int n, int m);

class Vector3 {
public:
	float x, y, z;
	Vector3();
	Vector3(float xInit, float yInit, float zInit);
	Vector3 operator+(Vector3 otherVector);
	Vector3 operator-(Vector3 otherVector);

	float length();
	float length_squared();
};




Vector3 operator*(float c, Vector3 vector); 
Vector3 operator*(Vector3 vector, float c);
float dot(Vector3 vector_a, Vector3 vector_b);
Vector3 cross(Vector3 vector_a, Vector3 vector_b);
Vector3 normalise(Vector3 vector);

class Ray {
public:
	Vector3 passesThrough;
	Vector3 parallelTo;

	Ray();
	Ray(Vector3 vector, Vector3 point);

	Vector3 pointOnRay(float t);
};

/*
 * Will add other colour representations in the future
 */
class Colour {
public:
	int red, green, blue;
	Colour();
	Colour(int r, int g, int b);


	Colour operator+(Colour otherColour);
	Colour operator-(Colour otherColour);

};

struct rayIntersection {
	bool intersected = false;
	Vector3 intersectionPoint;
	float t;
	Colour colour;
};


class Camera {
public:  
	Vector3 cameraLocation;
	Vector3 up;
	Vector3 viewingDirection; //Also the normal of the viewport for now
	float horizontal;
	float vertical;
	Vector3 upperLeftCorner = Vector3(-horizontal/2, vertical/2, viewingDirection.z); // change to viewport normal in the future
	//The plane containing up and right will be

	Camera();
	Camera(Vector3 location, Vector3 up, Vector3 viewingDirection, float horizontal, float vertical);
};

class Object {
public:
	virtual rayIntersection rayHit(Ray ray) = 0;
};

class Plane: public Object {
public:
	Vector3 normal;
	Vector3 point;
	Colour colour;

	Plane();
	Plane(Vector3 normal, Vector3 point, Colour colour);

	rayIntersection rayHit(Ray ray);
};

class Sphere: public Object{
public:
	float radius;
	Vector3 centre;
	Colour colour;

	Sphere();
	Sphere(float radius, Vector3 centre, Colour colour);

	rayIntersection rayHit(Ray ray);
};



bool compareRayIntersectionsByZ(rayIntersection a, rayIntersection b);