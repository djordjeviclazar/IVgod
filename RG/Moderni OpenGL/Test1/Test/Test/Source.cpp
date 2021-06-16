/*Refference:
* https://learnopengl.com/
* 
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

int windowHeight = 600, windowWidth = 800;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Drawing functions:
int DrawCoordinateAxes();
int DrawTruck();
int DrawGround();

// MACROS
#define PI 3.14159

#define CYLINDER_BASE_NX 0
#define CYLINDER_BASE_NZ 0
#define CYLINDER_UP_NY 1
#define CYLINDER_DOWN_NY -1
#define CYLINDER_SIDE_NX(alpha) cos(alpha)
#define CYLINDER_SIDE_NY 0
#define CYLINDER_SIDE_NZ(alpha) sin(alpha)

#define VECTOR_LENGTH(x, y, z) sqrt(x * x + y * y + z * z)

#define RADIANS(angle) angle * PI / 180

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Truck", 0, 0);
	if (window == 0)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { return -1; }

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Arrays:
	float* coordAxes = new float[24];

	while (1)
	{
		glClearColor(0.2f, 0.85f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawCoordinateAxes();
		DrawTruck();
		DrawGround();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 1;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int DrawCoordinateAxes()
{

}

int DrawTruck()
{

}

int DrawGround()
{

}
