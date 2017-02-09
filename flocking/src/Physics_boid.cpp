#include <glm/glm.hpp>
#include "Physics_boid.h"
#include <iostream>

//to remove
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"
#include <iostream>
using namespace std;

#define X_MIN -3
#define X_MAX 3
#define Y_MIN -3
#define Y_MAX 3
#define Z_MIN -7
#define Z_MAX -5

physics_boid::physics_boid() {
	position = glm::vec3(0.0f, 0.0f, -6.0f);
	velocity = glm::vec3(1.0f, 1.0f, 1.0f);
	acceleration = glm::vec3(1.0f, 1.0f, 1.0f);
	friction = glm::vec3(0.9f, 1.0f, 0.9f);
	lifetime = 700;
	radius = 1;
};
physics_boid::~physics_boid() {};


void physics_boid::check_out_of_bounds()
{
	// if out of bounds wrap round
	if (position.x < X_MIN)
	{
		position.x = X_MAX -1;
	}
	if (position.x > X_MAX)
	{
		position.x = X_MIN +1;
	}

	if (position.y < Y_MIN)
	{
		position.y = Y_MAX -1;
	}
	if (position.y > Y_MAX)
	{
		position.y = Y_MIN +1;
	}

	if (position.y < Y_MIN)
	{
		position.y = Y_MAX -1;
	}
	if (position.y > Y_MAX)
	{
		position.y = Y_MIN + 1;
	}
}

void physics_boid::calculate_position(double time_diff)
{
	velocity.x += acceleration.x * time_diff;
	position.x += velocity.x * time_diff + 0.5 * acceleration.x * pow(time_diff, 2);

	velocity.y += acceleration.y * time_diff;
	position.y += velocity.y * time_diff + 0.5 * acceleration.y * pow(time_diff, 2);

	velocity.z += acceleration.z * time_diff;
	position.z += velocity.z * time_diff + 0.5 * acceleration.z * pow(time_diff, 2);

	//std::cout << "vel" << glm::to_string(velocity) << std::endl;
//	std::cout << "time_diff" << time_diff << std::endl;
//	std::cout << "acceleration" << glm::to_string(acceleration) << std::endl;

	check_out_of_bounds();
}

void physics_boid::move_ball(double time_diff) {

	calculate_position(time_diff);

}

bool physics_boid::operator!=(physics_boid boid){
	if (position== boid.position && lifetime == boid.lifetime && mass == boid.mass)
	{
		return true;
	}
	else
	{
		return false;
	}
}
