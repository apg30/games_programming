#ifndef BOID_CONTROL_H
#define BOID_CONTROL_H

#include <algorithm>
#include "Physics_boid.h"


class Boid_control {
public:
	Boid_control();
	~Boid_control();

	// Functions.
	void generate_boids();
  void move_boids(float time_diff);

	std::vector<glm::vec3> align_boids();
	std::vector<glm::vec3> cohere_boids();
	std::vector<glm::vec3> seperate_boids();
	bool are_neighbours(physics_boid boid_1, physics_boid boid_2);
	glm::vec3 normalise_vector(glm::vec3 vector);

	// Member variables
  std::vector<physics_boid> boids;
};

#endif
