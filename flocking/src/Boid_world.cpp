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

//to remove
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"

#include <algorithm>

#include "Vector_library.h"
#include "Graphics.h"
#include "Shapes.h"
#include "Physics_boid.h"
#include "Boid_control.h"

// VARIABLES
bool		running = true;
Graphics	myGraphics;		// Runing all the graphics in this object
Cube		myCube;
int const no_of_boids = 100;

// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void load_geometry(int ball_no);

// All spheres and main sphere
Sphere	mySpheres[no_of_boids];

// Control object to interact with physics ball
Boid_control control;

float t = 0.001f;			// Global variable for animation

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	myCube.Load();
	myGraphics.SetOptimisations();		// Cull and depth testing
}

// Called to sphere(s). It loads exploded spheres unless otherwise specified
// by the parameters in which case it loads the main sphere.
void load_geometry(int ball_no = no_of_boids){
	for (int i = 0; i < ball_no; i++)
	{
		Sphere new_sphere;
		new_sphere.Load();
		new_sphere.fillColor = glm::vec4(
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		mySpheres[i]= new_sphere;
	}
}

// Update spheres' position, rotation and scale from corresponding boids
// attributes.
void update(double currentTime) {
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(0.0f, -2.0f, -6.0f)) *
		glm::mat4(1.0f);
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;

	// calculate Spheres' movement
	glm::mat4 mv_matrix_spheres;
//	int i=0;
//	for (Physics_boid n : control.boids)
	for(int i =0; i < no_of_boids; i++)
	{
		mv_matrix_spheres = glm::translate(control.boids[i].position) *
								//glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
								//glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
								glm::mat4(1.0f) *
								glm::scale(glm::vec3(control.boids[i].radius, control.boids[i].radius, control.boids[i].radius));
			mySpheres[i].mv_matrix = mv_matrix_spheres;
			mySpheres[i].proj_matrix = myGraphics.proj_matrix;
			std::cout << i << std::endl;
			//i++;
	}

	t += 0.01f; // increment movement variable
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	for (int i = 0; i< no_of_boids; i++)
	{
			 mySpheres[i].Draw();
	}
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
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
	}
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}

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

	control.generate_boids();
	load_geometry();

	double currentTime = glfwGetTime();

	do {													// MAIN LOOP run until the window is closed
		//calculate time difference
		double prev_time = currentTime;
		currentTime = glfwGetTime();
		double time_diff = currentTime - prev_time;

		// poll callbacks
		glfwPollEvents();

		update(currentTime);

		// apply physics to Physics_boids
		control.move_boids(time_diff);

		// render spheres.
		render(currentTime);

		// swap buffers (avoid flickering and tearing)
		glfwSwapBuffers(myGraphics.window);

		// exit if escape key pressed
		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);

	} while (running);

	// Close and clean everything up
	myGraphics.endProgram();

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}
