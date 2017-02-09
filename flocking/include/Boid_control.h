#ifndef BOID_CONTROL_H
#define BOID_CONTROL_H

#include <algorithm>
#include "Physics_boid.h"


class Boid_control {
public:
	Boid_control();
	~Boid_control();

  void move_boids(float time_diff);
  void generate_boids();
	std::vector<glm::vec3> align_boids();
	void cohere_boids();
	void seperate_boids();
	bool are_neighbours(physics_boid boid_1, physics_boid boid_2);

  std::vector<physics_boid> boids;
	physics_boid main_ball;
};

#endif
