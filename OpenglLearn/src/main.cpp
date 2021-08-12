#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include"Help.h"
#include"Texture.h"
#include"Matirx.h"

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

float vertices[] = {
	0.5,0.5,0.0f,      1.0f,0.0f,0.0f,  1.0f,1.0f,
	0.5f,-0.5f,0.0f,   0.0f,1.0f,0.0f,  1.0f,0.0f,
	-0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,
	-0.5,0.5,0.0f,     0.0f,1.0f,1.0f,  0.0f,1.0f
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
};


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
	//VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBO 
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//set first attribute
	glEnableVertexAttribArray(0);//enabel a generic buffer attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//set second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//set second attribute
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string path = Chelp::getDirectory();
	std::string vsPath = path + std::string("\\Shader\\shader.vs");
	std::string fsPath = path + std::string("\\Shader\\shader.fs");
	std::string picPath = path + std::string("\\Shader\\container.jpg");
	std::string picPath2 = path + std::string("\\Shader\\awesomeface.png");

	CTexture tex1(picPath.c_str(),GL_RGB,false);
	CTexture tex2(picPath2.c_str(),GL_RGBA,true);
	
	CShader ourShader(vsPath.c_str(),fsPath.c_str());
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	
	
	while (!glfwWindowShouldClose(window))//if GLFW has been instructed to close
	{
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
		
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		ourShader.setMatrix4fv("transform", glm::value_ptr(trans));
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0) + 0.5;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		//
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1.m_TexID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2.m_TexID);
		glBindVertexArray(VAO);//bind VAO auto bind EBO
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//swap color buffer
		glfwPollEvents();//check if any events are triggered(keyborad mousemove)
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}