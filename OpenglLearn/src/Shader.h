#pragma once
#include<glad/glad.h>

#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

class CShader
{
public:
	CShader();
	CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~CShader();

	unsigned int ID;
	

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:

};

CShader::CShader()
{
}

inline CShader::CShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentColor;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//make sure ifstrem throw error
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		//read file to buffer
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentColor = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentColor.c_str();

	//vertexshader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //create vertex shader
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
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
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER""VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

CShader::~CShader()
{
}

inline void CShader::use()
{
	glUseProgram(ID);
}

inline void CShader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

inline void CShader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

inline void CShader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
