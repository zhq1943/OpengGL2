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

float vertices[] = {
	0.5,0.5,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	-0.5,0.5,0.0f
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f,0.5f,0.2f,1.0f);"
"}\n";

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

	//vertex array object
	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);//element buffer object
	glGenBuffers(1, &VBO);//create vertex buffer object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind buffer to gl_array_buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//copy data to buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//copy indics data to buffer
	glEnableVertexAttribArray(0);

	//vertexshader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //create vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); //compile shader program

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//check compile is ok
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER""VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	while (!glfwWindowShouldClose(window))//if GLFW has been instructed to close
	{
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//swap color buffer
		glfwPollEvents();//check if any events are triggered(keyborad mousemove)
	}

	glfwTerminate();
	return 0;
}