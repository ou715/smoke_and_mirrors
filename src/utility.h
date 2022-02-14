#pragma once


struct PPM {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
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
	Vector3 parallelTo;
	Vector3 passesThrough;
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