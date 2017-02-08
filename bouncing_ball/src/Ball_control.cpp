#include "Ball_control.h"

int const no_of_balls = 100;

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
