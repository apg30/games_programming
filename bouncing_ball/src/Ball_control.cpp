#include "Ball_control.h"

extern int no_of_balls;

Ball_control::Ball_control(){
};
Ball_control::~Ball_control(){
};

void Ball_control::move_balls(float time_diff){
  int i = 0;
  for (auto it = balls.begin(); it != balls.end(
  ); it++,i++)	// Move every ball
  //	for (Physics_ball n : balls)
  {
    balls.at(i).move_ball(time_diff);
    //n.move_ball(time_diff);
  }
  		main_ball.move_ball(time_diff);
}

// Create new balls with random attributes.
// Create new spheres with random attributes
void Ball_control::explode()
{
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < no_of_balls; i++)
	{
		Physics_ball new_ball;
		new_ball.lifetime = rand() % 200 + 300;
		new_ball.radius = 0.02f;
		new_ball.position = main_ball.position;
		new_ball.velocity = glm::vec3(-7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (12))), -7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (16))), -7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (12))));
		new_ball.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
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
