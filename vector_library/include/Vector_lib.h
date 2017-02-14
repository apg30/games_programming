#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

#include <glm/glm.hpp>
class vec3 {

public:
	vec3();
	~vec3();
	vec3(float x, float y, float z);

	vec3 cross(vec3 vec);
	vec3 normalize();
	float dot(vec3 vec);
	float length();
	glm::vec3 toGLMVec3();
	
	bool operator==(vec3 vec);
	bool operator!=(vec3 vec);
	vec3 operator+(vec3 vec);
	vec3 operator-(vec3 vec);
	vec3 operator*(vec3 vec);
	vec3 operator/(vec3 vec);
	vec3 operator+=(const vec3 &vec);
	vec3 operator-=(const vec3 &vec);
	vec3 operator*=(const vec3 &vec);
	vec3 operator/=(const vec3 &vec);
	vec3 operator+(float scalar);
	vec3 operator-(float scalar);
	vec3 operator*(float scalar);
	vec3 operator/(float scalar);
	vec3 operator+=(float scalar);
	vec3 operator-=(float scalar);
	vec3 operator*=(float scalar);
	vec3 operator/=(float scalar);

	float x;
	float y;
	float z;
};

#endif
