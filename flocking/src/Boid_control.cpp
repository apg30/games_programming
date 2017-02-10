#define LOCAL_LEVEL 0.5
#define K_ALIGN 0.003
#define K_COHERE 0.003
#define K_SEPERATE 0.003

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


//Apply swarm behaviour
void Boid_control::move_boids(float time_diff){

  // find alignment from all 3 algorithms.
  std::vector<glm::vec3> seperate_velocity =  seperate_boids();
  std::vector<glm::vec3> align_velocity =  align_boids();
  std::vector<glm::vec3> cohere_velocity =  cohere_boids();

  // For every boid
  int i = 0;
  for (auto it = boids.begin(); it != boids.end(); it++,i++)
  {
    boids.at(i).velocity = seperate_velocity.at(i);
  //  boids.at(i).velocity += align_velocity.at(i);
  //  boids.at(i).velocity += cohere_velocity.at(i);

    boids.at(i).move_ball(time_diff);
  }
}

//***********************Movement algorithms***********************************
std::vector<glm::vec3> Boid_control::align_boids()
{
  std::vector<glm::vec3> align_velocity;
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
    alignmentment = normalise_vector(alignmentment);
    // Add Weighting
    alignmentment = alignmentment * K_ALIGN;
    // Normalise
    alignmentment = normalise_vector(alignmentment);    // Add to list.
    align_velocity.push_back(alignmentment);
  }
  return align_velocity;
}

std::vector<glm::vec3> Boid_control::cohere_boids()
{
  std::vector<glm::vec3> cohere_velocity;
  for (auto boid : boids)
  {
    int neighbours = 0;
    glm::vec3 centre_position;// = boid.position;

    for (auto potential_neighbour : boids)
    {
       if(are_neighbours(boid, potential_neighbour)) //TODO check it isn't equal to itself.
       {
         centre_position += potential_neighbour.position;
        // std::cout << "alignmentment: " << glm::to_string(alignmentment) << std::endl;
         neighbours +=1;
       }
    }
    // Averaging
    centre_position /= neighbours;
    // allignment_vector
    auto direction_vector = centre_position - boid.position;
    // Add weighting
    direction_vector *= K_COHERE;
    direction_vector = normalise_vector(direction_vector);
    cohere_velocity.push_back(direction_vector);
   }
   return cohere_velocity;
}

std::vector<glm::vec3> Boid_control::seperate_boids()
{
  std::vector<glm::vec3> seperation_velocity;
  for (auto boid : boids)
  {
    glm::vec3 direction_vector;

    for (auto potential_neighbour : boids)
    {
       if(are_neighbours(boid, potential_neighbour)) //TODO check it isn't equal to itself.
       {
         direction_vector = direction_vector + (boid.position - potential_neighbour.position);
       }
    }
    direction_vector *= K_SEPERATE;
    direction_vector = normalise_vector(direction_vector);
    seperation_velocity.push_back(direction_vector);
   }
   return seperation_velocity;
}

//*****************************************************************************
glm::vec3 Boid_control::normalise_vector(glm::vec3 vector)
{
  vector /= sqrt(pow(vector.x,2) + pow(vector.y,2) + pow(vector.z,2));
  return vector;
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
		new_ball.radius = 0.1f;
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
