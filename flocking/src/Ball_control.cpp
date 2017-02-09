#include "Ball_control.h"

extern int no_of_balls;

Ball_control::Ball_control(){
};
Ball_control::~Ball_control(){
};

//Apply physics to every ball
void Ball_control::move_boids(float time_diff){
  int i = 0;
  for (auto it = balls.begin(); it != balls.end(); it++,i++)
  {
    balls.at(i).move_ball(time_diff);
  }
  		main_ball.move_ball(time_diff);
}

// Create new balls with random attributes.
// Create new spheres with random attributes
void Ball_control::generate_boids()
{
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < no_of_balls; i++)
	{
		Physics_ball new_ball;
		new_ball.lifetime = rand() % 200 + 500;
		new_ball.radius = 0.02f;
		new_ball.position = glm::vec3(
               -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))),
               -3  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))),
               -9  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))));;
		new_ball.velocity =
      glm::vec3(
      -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4))),
      -2  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4))),
      -2  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4))));
		balls.push_back(new_ball);
	}
}
