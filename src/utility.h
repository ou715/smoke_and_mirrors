#pragma once


struct PPM {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

PPM transpose(PPM image, int n, int m);

class Vector3 {
public:
	float x, y, z;
	Vector3(float xInit, float yInit, float zInit);

	Vector3 operator+ ();

	float length();

};

