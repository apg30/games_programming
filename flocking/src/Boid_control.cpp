#define LOCAL_LEVEL 2
#define K_ALIGN 0.3
#define K_COHERE 0.3
#define K_SEPERATE 0.3

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
  //  boids.at(i).velocity += seperate_velocity.at(i);
    boids.at(i).velocity += align_velocity.at(i);
  //  boids.at(i).velocity += cohere_velocity.at(i);

    // Move ball: it checks top speed and if out of bounds
    boids.at(i).move_ball(time_diff);
  }
}

//***********************Movement algorithms***********************************
std::vector<glm::vec3> Boid_control::align_boids()
{
  // List of velocity vectors
  std::vector<glm::vec3> align_velocity;
  // For every boid
  for (auto boid : boids)
  {
    // The alignment for each boid.
    glm::vec3 alignment;
    int neighbours = 0;
    // Find out if boid and other boid are a neighbour.
    for (auto potential_neighbour : boids)
    {
      // Check boid if not itself &  Check other boid is in the neighbourhood
      if(boid != potential_neighbour && are_neighbours(boid, potential_neighbour))
      {
         // Total neighbours velocities
         alignment += potential_neighbour.velocity;
         // Keep track of number of neighbours
         neighbours +=1;
       }
    }
    if(neighbours == 0)
    {
      align_velocity.push_back(glm::vec3(0.0f, 0.0f,0.0f));
    }
    else
    {
    // Find average velocity of neighours.
    alignment = alignment / float(neighbours);
    // Normalise vector
    //alignment = normalise_vector(alignment);
    // Add Weighting
    alignment = alignment * K_ALIGN;
    // Normalise
    // alignment = normalise_vector(alignment);
    // Add to list.
    align_velocity.push_back(alignment);
    }
  }
  return align_velocity;
}

std::vector<glm::vec3> Boid_control::cohere_boids()
{
  // List for the cohere velocity of each boid
  std::vector<glm::vec3> cohere_velocity;
  // For each boid
  for (auto boid : boids)
  {
    int neighbours = 0;
    // The centre position of all the boids in the neighbourhood
    glm::vec3 centre_position;
    glm::vec3 direction_vector;
    // For every boid
    for (auto potential_neighbour : boids)
    {
      // Check boid if not itself & Check other boid is in the neighbourhood
      if(boid != potential_neighbour && are_neighbours(boid, potential_neighbour))
      {
           // Add up all neighbours positions.
           centre_position += potential_neighbour.position;
          // Keep track of number of neighbours.
           neighbours +=1;
      }
    }
    if (neighbours ==0){
      cohere_velocity.push_back(glm::vec3(0.0f,0.0f,0.0f));
    }
    else
    {
    // Averaging to find centre position.
    centre_position /= neighbours;
    // Get direction from current position to centre position.
    direction_vector = centre_position - boid.position;
    // Normalise
  //direction_vector = normalise_vector(direction_vector);
    // Add weighting
    direction_vector *= K_COHERE;
    // Normalise
  //direction_vector = normalise_vector(direction_vector);
    // Add to velocity list.
    cohere_velocity.push_back(direction_vector);
    }
  }
  return cohere_velocity;
}

std::vector<glm::vec3> Boid_control::seperate_boids()
{
  // List for seperation velocity for each boid
  std::vector<glm::vec3> seperation_velocity;
  // For each boid
  for (auto boid : boids)
  {
    // The direction vector for the boid
    glm::vec3 direction_vector;
    for (auto potential_neighbour : boids)
    {
      // Check boid is not itself & Check other boid is in the neighbourhood
      if (boid != potential_neighbour && are_neighbours(boid, potential_neighbour))
      {
         direction_vector = direction_vector - (boid.position - potential_neighbour.position);
      }
    }
    direction_vector *= K_SEPERATE;
  //direction_vector = normalise_vector(direction_vector);
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
		boids.push_back(new_ball);
	}
}
