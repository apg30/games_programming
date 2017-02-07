//unit tests
#define BOOST_TEST_MODULE "Unit test module for vector library"
#include <boost/test/unit_test.hpp>
#include<iostream>
#include "vector_library.h"
using namespace std;


BOOST_AUTO_TEST_SUITE(VECTOR_LIBRARY_TEST_SUITE)

// ****************************************************************************
// Misc functions
BOOST_AUTO_TEST_CASE(length){
  Vector_3d test_vector(6,6,7);
  float vector_length = test_vector.length();
  BOOST_CHECK(vector_length == 11);
}

BOOST_AUTO_TEST_CASE(equivalence){
  Vector_3d test_vector(3,3,3);
  Vector_3d test_vector2(3,3,3);
  BOOST_CHECK(test_vector.equivalence(test_vector2) == 1);
}

BOOST_AUTO_TEST_CASE(dot_product){
  Vector_3d test_vector(1,2,3);
  Vector_3d test_vector2(4,5,6);
  float result = test_vector.dot_product(test_vector2);
  BOOST_CHECK(result == 32);
}

BOOST_AUTO_TEST_CASE(cross_product){
  Vector_3d test_vector(1,2,3);
  Vector_3d test_vector2(4,5,6);
  Vector_3d expected_vector(-3,6,-3);
  Vector_3d result_vector = test_vector.cross_product(test_vector2);
  BOOST_CHECK(expected_vector.equivalence(result_vector) == 1);
}
// ****************************************************************************
// Vector Arithmetic
BOOST_AUTO_TEST_CASE(vector_addition){
  Vector_3d test_vector(3,3,3);
  Vector_3d test_vector2(5,5,5);
  Vector_3d expected_vector(8,8,8);
  Vector_3d result = test_vector.vector_addition(test_vector2);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}
BOOST_AUTO_TEST_CASE(vector_subraction){
  Vector_3d test_vector(10,10,10);
  Vector_3d test_vector2(4,4,4);
  Vector_3d expected_vector(6,6,6);
  Vector_3d result = test_vector.vector_subtraction(test_vector2);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}
BOOST_AUTO_TEST_CASE(vector_multiplication){
  Vector_3d test_vector(3,3,3);
  Vector_3d test_vector2(5,5,5);
  Vector_3d expected_vector(15,15,15);
  Vector_3d result = test_vector.vector_multiplication(test_vector2);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}
BOOST_AUTO_TEST_CASE(vector_division){
  Vector_3d test_vector(15,15,15);
  Vector_3d test_vector2(5,5,5);
  Vector_3d expected_vector(3,3,3);
  Vector_3d result = test_vector.vector_division(test_vector2);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}
// ****************************************************************************
// Scalar Arithmetic
BOOST_AUTO_TEST_CASE(scalar_addition){
  Vector_3d test_vector(3,3,3);
  float scalar = 5;
  Vector_3d expected_vector(8,8,8);
  Vector_3d result = test_vector.scalar_addition(scalar);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}

BOOST_AUTO_TEST_CASE(scalar_subraction){
  Vector_3d test_vector(10,10,10);
  float scalar = 5;
  Vector_3d expected_vector(5,5,5);
  Vector_3d result = test_vector.scalar_subtraction(scalar);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}

BOOST_AUTO_TEST_CASE(scalar_multiplication){
  Vector_3d test_vector(3,3,3);
  float scalar = 5;
  Vector_3d expected_vector(15,15,15);
  Vector_3d result = test_vector.scalar_multiplication(scalar);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}
BOOST_AUTO_TEST_CASE(scalar_division){
  Vector_3d test_vector(20,20,20);
  float scalar = 5;
  Vector_3d expected_vector(4,4,4);
  Vector_3d result = test_vector.scalar_division(scalar);
  BOOST_CHECK(expected_vector.equivalence(result) == 1 );
}

BOOST_AUTO_TEST_SUITE_END()
