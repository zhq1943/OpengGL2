#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();//Initialize GLFW 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Set major veriosn
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//Set minor verison
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Set to use core-profile then we can sccess to a small subset

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//set window context as main context

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//call this function on every window resize

	while (!glfwWindowShouldClose(window))//if GLFW has been instructed to close
	{
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);//swap color buffer
		glfwPollEvents();//check if any events are triggered(keyborad mousemove)
	}

	glfwTerminate();
	return 0;
}