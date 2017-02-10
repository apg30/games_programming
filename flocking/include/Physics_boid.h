#ifndef PHYSCIS_BOID_H
#define PHYSCIS_BOID_H

#include <glm/glm.hpp>

class physics_boid {
public:
	physics_boid();
	~physics_boid();
	void check_out_of_bounds();
	void check_top_speed();

	void calculate_position(double time_diff);
	bool operator!=(physics_boid boid);
	void move_ball(double time_diff);

	glm::vec3 friction;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float lifetime;
	float mass;
	float radius;
private:


};

#endif
