// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
//
// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#define TRANSPARENCY_RATE 0.008

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"
#include <algorithm>

#include "Vector_library.h"
#include "Graphics.h"
#include "Shapes.h"
#include "Physics_ball.h"
#include "Ball_control.h"


// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void remove_dead();

// VARIABLES
bool		running = true;
Graphics	myGraphics;		// Runing all the graphics in this object
Cube		myCube;
int const no_of_balls = 100;

// Where all the balls are stored
std::vector<Sphere>		mySpheres;


Ball_control control;
// The main is the only one which can be exploded.
Sphere main_sphere;

float t = 0.001f;			// Global variable for animation

int main()
{

	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				// Close if something went wrong...
	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys

  glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double currentTime = glfwGetTime();

	do {													// MAIN LOOP run until the window is closed
		double prev_time = currentTime;
		currentTime = glfwGetTime();		// retrieve timelapse
		double time_diff = currentTime - prev_time;

		glfwPollEvents();						// poll callbacks

		update(currentTime);					// update (physics, animation, structures, etc)

		control.move_balls(time_diff);


		remove_dead();							// remove dead balls
		render(currentTime);					// call render function.

		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);

	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}


// Removes physics ball and graphics ball for dead balls.
// Must be done this way to avoid manipulating the iterator whilst iterating.
void remove_dead() {

	auto balls = control.balls;
	int i = 0;
	for (auto it = balls.cbegin(); it != balls.cend(); )
	{
		if (!balls.at(i).is_alive())
		{
			it = balls.erase(balls.begin() + i);
 			mySpheres.erase(mySpheres.begin() + i);
		}
		else
		{
			float alpha = balls.at(i).lifetime * TRANSPARENCY_RATE;
			mySpheres.at(i).fillColor = glm::vec4(0.0f, 1.0f, 0.0f, alpha);
			it++;
			i++;
		}
	}
	balls.shrink_to_fit();
	mySpheres.shrink_to_fit();

	if(control.main_ball.is_alive())
	{
		float alpha = control.main_ball.lifetime * TRANSPARENCY_RATE;
		main_sphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, alpha);
	}
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	main_sphere.Load();
	main_sphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	myCube.Load();
	myGraphics.SetOptimisations();		// Cull and depth testing
}

void load_geometry(glm::vec4 colour = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX))){
// Load Geometry
	for (int i = 0; i < no_of_balls; i++)
	{
		Sphere new_sphere;
		new_sphere.Load();
		new_sphere.fillColor = colour;
		mySpheres.push_back(new_sphere);
	}
}

void update(double currentTime) {

	auto balls = control.balls;
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(0.0f, -2.0f, -6.0f)) *
		glm::mat4(1.0f);
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;

	// calculate Spheres' movement
	glm::mat4 mv_matrix_spheres;

	int i=0;
	for (Physics_ball n : balls)
	{
		mv_matrix_spheres = glm::translate(n.position) *
								//glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
								//glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
								glm::mat4(1.0f) *
								glm::scale(glm::vec3(n.radius, n.radius, n.radius));
			mySpheres.at(i).mv_matrix = mv_matrix_spheres;
			mySpheres.at(i).proj_matrix = myGraphics.proj_matrix;
			i++;
	}

	// calculate  main sphere's movement
	glm::mat4 main_mv_matrix_sphere =	glm::translate(control.main_ball.position) *
										//glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
										//glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
										glm::mat4(1.0f);
	main_sphere.mv_matrix = main_mv_matrix_sphere;
	main_sphere.proj_matrix = myGraphics.proj_matrix;

	t += 0.01f; // increment movement variable
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	for (Sphere mySphere : mySpheres)
	{
			mySphere.Draw();
	}
	if (control.main_ball.is_alive()){
		main_sphere.Draw();
	}

		//myCube.Draw();
}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		control.explode();
		load_geometry();
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		control.generate_ball();
		load_geometry(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	}
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}
