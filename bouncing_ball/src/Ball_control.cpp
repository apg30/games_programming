#include "Ball_control.h"

extern int no_of_balls;

Ball_control::Ball_control(){
};
Ball_control::~Ball_control(){
};

//Apply physics to every ball
void Ball_control::move_balls(float time_diff){
  int i = 0;
  for (auto it = balls.begin(); it != balls.end(); it++,i++)
  {
    balls.at(i).move_ball(time_diff);
  }
  		main_ball.move_ball(time_diff);
}

// Create new balls with random attributes.
// Create new spheres with random attributes
void Ball_control::explode()
{
  // If main ball exists explode main ball.
  // Otherwise explode from random location.
  auto position = main_ball.position;
  if (!main_ball.is_alive())
  {
    position = glm::vec3(
               -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))),
               -3  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))),
               -9  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))));
  }
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < no_of_balls; i++)
	{
		Physics_ball new_ball;
		new_ball.lifetime = rand() % 200 + 500;
		new_ball.radius = 0.02f;
		new_ball.position = position;
		new_ball.velocity =
      glm::vec3(
      -7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (16))),
      -7  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (25))),
      -7  + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (16))));
		balls.push_back(new_ball);
	}
	// Kill main ball - set to 5 for small delay.
	main_ball.lifetime = 5;
}

void Ball_control::generate_ball() {

	balls.push_back(main_ball);

	srand(static_cast <unsigned> (time(0)));
		Physics_ball new_ball;
		new_ball.lifetime = rand() % 200 + 300;
		new_ball.radius = 1.0f;
	//	balls.push_back(new_ball);
		main_ball = new_ball;
}

// Removes physics ball and graphics ball for dead balls.
// Must be done this way to avoid manipulating the iterator whilst iterating.
std::vector<int> Ball_control::remove_dead_balls() {

  std::vector<int> removed_ball_index;
	int i = 0;
	for (auto it = balls.cbegin(); it != balls.cend(); )
	{
		if (!balls.at(i).is_alive())
		{
			it = balls.erase(balls.begin() + i);
      removed_ball_index.push_back(i);
 		//	mySpheres.erase(mySpheres.begin() + i);
		}
		else
		{
			it++;
			i++;
		}
	}
	balls.shrink_to_fit();
  return removed_ball_index;
}
