#define LOCAL_LEVEL 2
#define K 2

#include <algorithm>    // std::max
#include <iostream>
#include "Boid_control.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"
using namespace std;

extern int no_of_boids;

Boid_control::Boid_control(){
};
Boid_control::~Boid_control(){
};

glm::vec3 top_velocity(glm::vec3 velocity){
  velocity.x = min(1.0f,velocity.x);
  velocity.y = min(1.0f,velocity.y);
  velocity.z = min(1.0f,velocity.z);
  return velocity;
}

//Apply swarm behaviour
void Boid_control::move_boids(float time_diff){

  // find alignment from all 3 algorithms.
  auto combined_alignment = align_boids()  ; //other calculations

  // For every boid
  int i = 0;
  for (auto it = boids.begin(); it != boids.end(); it++,i++)
  {
    boids.at(i).velocity += combined_alignment.at(i);
    // Cap out top weight.
    boids.at(i).velocity = top_velocity(boids.at(i).velocity);

    boids.at(i).calculate_position(time_diff);
  }
}

std::vector<glm::vec3> Boid_control::align_boids()
{
  std::vector<glm::vec3> align_boids_alignment;
  for (auto boid : boids)
  {
    int neighbours = 0;
    auto alignmentment = boid.velocity;

    for (auto potential_neighbour : boids)
    {
       if(are_neighbours(boid, potential_neighbour)) //TODO check it isn't equal to itself.
       {
         alignmentment += potential_neighbour.velocity;
        // std::cout << "alignmentment: " << glm::to_string(alignmentment) << std::endl;
         neighbours +=1;
       }
    }
    alignmentment /= neighbours;
    // Normalise
    alignmentment /= sqrt(pow(alignmentment.x,2) + pow(alignmentment.y,2) + pow(alignmentment.z,2));
    // Add Weighting
    alignmentment = alignmentment * K;
    // Normalise
    alignmentment /= sqrt(pow(alignmentment.x,2) + pow(alignmentment.y,2) + pow(alignmentment.z,2));
    // Add to list.
    align_boids_alignment.push_back(alignmentment);
  }
  return align_boids_alignment;
}

void Boid_control::cohere_boids()
{

}

void Boid_control::seperate_boids()
{

}

bool Boid_control::are_neighbours(physics_boid boid_1, physics_boid boid_2)
{
   auto diff_x = abs(boid_1.position.x - boid_2.position.x);
   auto diff_y = abs(boid_1.position.y - boid_2.position.y);
   auto diff_z = abs(boid_1.position.z - boid_2.position.z);

   if ( diff_x < LOCAL_LEVEL && diff_y < LOCAL_LEVEL && diff_z && LOCAL_LEVEL)
   {
     return true;
   }
   return false;
}




// Create new boids with random attributes.
// Create new spheres with random attributes
void Boid_control::generate_boids()
{
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < no_of_boids; i++)
	{
		physics_boid new_ball;
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
    new_ball.mass = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20)));
		boids.push_back(new_ball);
	}
}
