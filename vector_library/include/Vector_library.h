#ifndef VECTOR_3D_LIBRARY_H
#define VECTOR_3D_LIBRARY_H

class Vector_3d{
  public:
    // Constructor and desctructor
    Vector_3d();
    Vector_3d(float x,float y ,float z);

    // Misc functions
    void print_vector();
    float length();
    bool equivalence(Vector_3d rhs);
    float dot_product(Vector_3d rhs);
    Vector_3d cross_product(Vector_3d rhs);

    // Vector Arithmetic
    Vector_3d vector_addition(Vector_3d rhs);
    Vector_3d vector_subtraction(Vector_3d rhs);
    Vector_3d vector_multiplication(Vector_3d rhs);
    Vector_3d vector_division(Vector_3d rhs);

    // Scalar Arithmetic
    Vector_3d scalar_addition(float scalar);
    Vector_3d scalar_subtraction(float scalar);
    Vector_3d scalar_multiplication(float scalar);
    Vector_3d scalar_division(float scalar);

    float x;
    float y;
    float z;

};

#endif
