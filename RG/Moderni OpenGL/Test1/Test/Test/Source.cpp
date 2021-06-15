/*Refference:
* https://learnopengl.com/
* 
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int windowHeight = 600, windowWidth = 800;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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

	while (1)
	{
		glClearColor(0.2f, 0.85f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
