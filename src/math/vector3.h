#pragma once
#include <cmath>

class Vector3 {
public:
	float x, y, z;
	Vector3();
	Vector3(float xInit, float yInit, float zInit);

	/**
	* \return vector with coordinates multiplied by -1
	*/
	Vector3 operator-();

	/**
	 * \param otherVector the vector to be added
	 * \return sum of two vectors
	 */
	Vector3 operator+(Vector3 otherVector);
	Vector3 operator-(Vector3 otherVector);

	float length();
	float length_squared();
};

/**
 * \brief Handles multiplication of a scalar with a given vector
 * \return Vector multiplied by a scalar
 */
Vector3 operator*(float c, Vector3 vector);

/**
 * \brief Handles multiplication of a given vector with a scalar
 * \return Vector multiplied by a scalar
 */
Vector3 operator*(Vector3 vector, float c);

/**
 * \brief Handles division of a given vector with a scalar
 * \return Vector divided by a scalar
 */
Vector3 operator/(Vector3 vector, float c);

/**
 * \brief Scalar (dot) product of two vectors
 * \param vector_a First vector
 * \param vector_b Second vector
 * \return Scalar product of 2 vectors
 */
float dot(Vector3 vector_a, Vector3 vector_b);

/**
 * \param vector_a First vector
 * \param vector_b Second vector
 * \return Vector product of two vectors
 */
Vector3 cross(Vector3 vector_a, Vector3 vector_b);

/**
 * \brief Function for normalising a vector
 * \param vector Input vector
 * \return Input vectored normalised to length 1
 */
Vector3 normalise(Vector3 vector);