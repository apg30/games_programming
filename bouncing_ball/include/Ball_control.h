#ifndef BALL_CONTROL
#define BALL_CONTROL

#include <algorithm>
#include "Physics_ball.h"


class Ball_control {
public:
	Ball_control();
	~Ball_control();

  void move_balls(float time_diff);
  void explode();
  void generate_ball();

  std::vector<Physics_ball> balls;
	Physics_ball main_ball;
};

#endif
