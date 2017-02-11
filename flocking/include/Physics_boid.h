#ifndef PHYSCIS_BOID_H
#define PHYSCIS_BOID_H

#include <glm/glm.hpp>

class Physics_boid {
public:
	Physics_boid();
	~Physics_boid();
	void check_out_of_bounds();
	void check_top_speed();

	void calculate_position(double time_diff);
	bool operator!=(Physics_boid boid);
	void move_ball(double time_diff);

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float radius;
private:


};

#endif
