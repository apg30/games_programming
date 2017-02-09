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


  std::vector<physics_boid> balls;
	physics_boid main_ball;
};

#endif
