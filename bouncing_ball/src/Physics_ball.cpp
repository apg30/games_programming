#include <glm/glm.hpp>
#include "Physics_ball.h"
#define GROUND -2
#define NOISE 0.2

#include <iostream>

Physics_ball::Physics_ball() {
	position = glm::vec3(0.0f, 0.0f, -6.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	friction = glm::vec3(0.9f, 1.0f, 0.9f);
	lifetime = 700;
	radius = 1;
};
Physics_ball::~Physics_ball() {};

// Set balls new velocity. calculate balls new position. decrement balls lifetime.
void Physics_ball::move_ball(double time_diff) {

	if (has_hit_ground(position))
	{
		velocity.y = -velocity.y * 0.9;
		//Add noise
		if (velocity.y > 0.3)
		{
			if ((rand() % 2) == 1)
			{
				velocity.x += NOISE;
			}
			else
			{
				velocity.x -= NOISE;
			}
		}
		else {
			add_friction();
		}
	}
	calculate_position(time_diff);
	decrement_lifetime();
}

void Physics_ball::add_friction() {
	velocity.x *= friction.x;
	velocity.y *= friction.y;
	velocity.z *= friction.z;
}

void Physics_ball::decrement_lifetime() {
	lifetime -= 1;
	if (lifetime < 0)
	{
		lifetime = 0;
	}
	std::cout << lifetime << std::endl;
}

bool Physics_ball::is_alive()
{
	if (lifetime > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Physics_ball::has_hit_ground(glm::vec3 position)
{
	if (position.y <= GROUND)
	{
		return true;
	}
	else
		return false;
}

void Physics_ball::calculate_position(double time_diff)
{
	velocity.x += acceleration.x * time_diff;
	position.x += velocity.x * time_diff + 0.5 * acceleration.x * pow(time_diff, 2);

	velocity.y += acceleration.y * time_diff;
	position.y += velocity.y * time_diff + 0.5 * acceleration.y * pow(time_diff, 2);

	velocity.z += acceleration.z * time_diff;
	position.z += velocity.z * time_diff + 0.5 * acceleration.z * pow(time_diff, 2);

	//Boundaries
	if (position.y < GROUND)
	{
		position.y = GROUND;
	}
}
