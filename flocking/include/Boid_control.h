#ifndef BOID_CONTROL_H
#define BOID_CONTROL_H
#define NO_OF_BOIDS 100

#include <algorithm>
#include "Physics_boid.h"


class Boid_control {
public:
	Boid_control();
	~Boid_control();

	// Functions.
	void generate_boids();
  void move_boids(float time_diff);

	void align_boids();
	void cohere_boids();
	void seperate_boids();
	bool are_neighbours(physics_boid boid_1, physics_boid boid_2);
	glm::vec3 normalise_vector(glm::vec3 vector);

	// Member variables
	glm::vec3 align_velocities[NO_OF_BOIDS];
	glm::vec3 cohere_velocities[NO_OF_BOIDS];
	glm::vec3 seperate_velocities[NO_OF_BOIDS];

  physics_boid boids[NO_OF_BOIDS];
};

#endif
