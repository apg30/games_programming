#include "vector_library.h"
#include <math.h>
#include<iostream>

// ****************************************************************************
// Constructors
Vector_3d::Vector_3d(){
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

Vector_3d::Vector_3d(float x, float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
}
// ****************************************************************************
// Misc functions
void Vector_3d::print_vector(){
  std::cout << "x: "<< x << " y: " << y << "  z: " << z << std::endl;
}

float Vector_3d::length() {
    return float(sqrt( x*x + y*y + z*z ));
}

bool Vector_3d::equivalence(Vector_3d rhs) {
    return(x == rhs.x && y == rhs.y && z == rhs.z);
}

float Vector_3d::dot_product(Vector_3d rhs){
 float result = (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
 return result;
}

Vector_3d Vector_3d::cross_product(Vector_3d rhs){
  Vector_3d result = Vector_3d(y * rhs.z - z * rhs.y,
                               z * rhs.x - x * rhs.z,
                               x * rhs.y - y * rhs.x);
  return result;
}
// ****************************************************************************
// Vector Arithmetic
Vector_3d Vector_3d::vector_addition(Vector_3d rhs){
  Vector_3d result_vector = Vector_3d(x + rhs.x, y + rhs.y, z + rhs.z);
  return result_vector;
}

Vector_3d Vector_3d::vector_subtraction(Vector_3d rhs){
  Vector_3d result_vector = Vector_3d(x - rhs.x, y - rhs.y, z - rhs.z);
  return result_vector;
}

Vector_3d Vector_3d::vector_multiplication(Vector_3d rhs){
  Vector_3d result_vector = Vector_3d(x * rhs.x, y * rhs.y, z * rhs.z);
  return result_vector;
}
Vector_3d Vector_3d::vector_division(Vector_3d rhs){
  Vector_3d result_vector = Vector_3d(x / rhs.x, y / rhs.y, z / rhs.z);
  return result_vector;
}

// ****************************************************************************
// Scalar Arithmetic
Vector_3d Vector_3d::scalar_addition(float scalar){
  Vector_3d result_vector = Vector_3d(x + scalar, y + scalar, z + scalar);
  return result_vector;
}

Vector_3d Vector_3d::scalar_subtraction(float scalar){
  Vector_3d result_vector = Vector_3d(x - scalar, y - scalar, z - scalar);
  return result_vector;
}

Vector_3d Vector_3d::scalar_multiplication(float scalar){
  Vector_3d result_vector = Vector_3d(x * scalar, y * scalar, z * scalar);
  return result_vector;
}
Vector_3d Vector_3d::scalar_division(float scalar){
  Vector_3d result_vector = Vector_3d(x / scalar, y / scalar, z / scalar);
  return result_vector;
}
