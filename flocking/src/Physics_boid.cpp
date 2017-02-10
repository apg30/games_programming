#include <glm/glm.hpp>
#include "Physics_boid.h"
#include <iostream>

//to remove
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"
#include <iostream>
using namespace std;

#define X_MIN -3.0f
#define X_MAX 3.0f
#define Y_MIN X_MIN
#define Y_MAX X_MAX
#define Z_MIN -9.0f
#define Z_MAX -3.0f
#define BOUNDARY_BUFFER 0.05f
#define MAX_SPEED 2

physics_boid::physics_boid() {
	position = glm::vec3(0.0f, 0.0f, -6.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	radius = 1;
};
physics_boid::~physics_boid() {};

void physics_boid::move_ball(double time_diff) {
	check_top_speed();
	calculate_position(time_diff);
	check_out_of_bounds();
}

void physics_boid::calculate_position(double time_diff)
{
	velocity.x += acceleration.x * time_diff;
	position.x += velocity.x * time_diff + 0.5 * acceleration.x * pow(time_diff, 2);

	velocity.y += acceleration.y * time_diff;
	position.y += velocity.y * time_diff + 0.5 * acceleration.y * pow(time_diff, 2);

	velocity.z += acceleration.z * time_diff;
	position.z += velocity.z * time_diff + 0.5 * acceleration.z * pow(time_diff, 2);
}

void physics_boid::check_top_speed(){
  if (velocity.x > MAX_SPEED){
    velocity.x = (velocity.x / abs(velocity.x) * MAX_SPEED);
  }
  if (velocity.y > MAX_SPEED){
    velocity.y = (velocity.y / abs(velocity.y) * MAX_SPEED);
  }
  if (velocity.z > MAX_SPEED){
    velocity.z = (velocity.z / abs(velocity.z) * MAX_SPEED);
  }
}

void physics_boid::check_out_of_bounds()
{
	// if out of bounds wrap round
	if (position.x < X_MIN)
	{
		position.x = X_MAX - BOUNDARY_BUFFER;
	}
	if (position.x > X_MAX)
	{
		position.x = X_MIN + BOUNDARY_BUFFER;
	}

	if (position.y < Y_MIN)
	{
		position.y = Y_MAX - BOUNDARY_BUFFER;
	}
	if (position.y > Y_MAX)
	{
		position.y = Y_MIN + BOUNDARY_BUFFER;
	}

	//if out of bounds come back round slowly.
	if (position.z < Z_MIN)
	{
		velocity.z = velocity.z + 5; //position.z = Z_MAX - BOUNDARY_BUFFER;
	}
	if (position.z > Z_MAX)
	{
		velocity.z = velocity.z - 5; //Z_MIN + BOUNDARY_BUFFER;
	}

}

bool physics_boid::operator!=(physics_boid boid){
	if (position == boid.position && velocity == boid.velocity)
	{
		return false;
	}
	else
	{
		return true;
	}
}
