#ifndef BALL_CONTROL
#define BALL_CONTROL

#include <algorithm>
#include "Physics_ball.h"


class Ball_control {
public:
	Ball_control();
	~Ball_control();

  void move_boids(float time_diff);
  void generate_boids();


  std::vector<Physics_ball> balls;
	Physics_ball main_ball;
};

#endif
