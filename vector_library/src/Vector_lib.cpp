#include "Vectors.h"
#include <GLM/glm.hpp>

vec3::vec3() {};
vec3::~vec3() {};
vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
};

vec3 vec3::cross(vec3 vec) {
	return vec3(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

float vec3::dot(vec3 vec) {
	return (x*vec.x + y*vec.y + z*vec.z);
}

float vec3::length() {
	return (sqrt(x*x + y*y + z*z));
}

vec3 vec3::normalize() {
	return vec3(x / length(), y / length(), z / length());
}

glm::vec3 vec3::toVec3() {
	return glm::vec3(x, y, z);
}

bool vec3::operator==(vec3 vec) {
	return(x == vec.x && y == vec.y && z == vec.z);
}

bool vec3::operator!=(vec3 vec) {
	return(x != vec.x || y != vec.y || z != vec.z);
}

vec3 vec3::operator+(vec3 vec) {
	return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator-(vec3 vec) {
	return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 vec3::operator*(vec3 vec) {
	return vec3(x * vec.x, y * vec.y, z * vec.z);
}

vec3 vec3::operator/(vec3 vec) {
	return vec3(x / vec.x, y / vec.y, z / vec.z);
}

vec3 vec3::operator+=(const vec3 &vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

vec3 vec3::operator-=(const vec3 &vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

vec3 vec3::operator*=(const vec3 &vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

vec3 vec3::operator/=(const vec3 &vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

vec3 vec3::operator+(float scalar) {
	return vec3(x + scalar, y + scalar, z + scalar);
}

vec3 vec3::operator-(float scalar) {
	return vec3(x - scalar, y - scalar, z - scalar);
}

vec3 vec3::operator*(float scalar) {
	return vec3(x * scalar, y * scalar, z * scalar);
}

vec3 vec3::operator/(float scalar) {
	return vec3(x / scalar, y / scalar, z / scalar);
}

vec3 vec3::operator+=(float scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

vec3 vec3::operator-=(float scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

vec3 vec3::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

vec3 vec3::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}



;
