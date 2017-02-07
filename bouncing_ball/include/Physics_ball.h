#ifndef PHYSICS_BALL_H
#define PHYSICS_BALL_H

#include <glm/glm.hpp>

class Physics_ball {
public:
	Physics_ball();
	~Physics_ball();
	void move_ball(double time_diff);
	bool has_hit_ground(glm::vec3 position);
	void calculate_position(double time_diff);
	void add_friction();
	void decrement_lifetime();
	bool is_alive();

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
