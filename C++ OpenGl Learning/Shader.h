#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include<glew.h>

#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>

class Shader
{
private:
	//Member varbles
	GLuint id;

	//Privatefunctions
	std::string loadShaderSource(const char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;


		//vertex
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_VERTEX_FILE: " << fileName << "\n";
		}

		in_file.close();
		return src;
	}

	GLuint loadShader(GLenum type,const char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER" << fileName << "\n";
			std::cout << infoLog << "\n";
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);
		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this -> id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADERS::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}

public:
	//Constructors/Destructors
	Shader(const char* vertexFile = "", const char* fragmentFile = "", const char* geometryFile = "")
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
		if (geometryFile != "")
		{
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		//End

		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	void Set1i(GLint value, const GLchar* name)
	{
		this->Use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
		this->UnUse();
	}

	//set uniform function
	void Use()
	{
		glUseProgram(this->id);
	}

	void UnUse()
	{
		glUseProgram(0);
	}

	void SetVector1f(GLfloat value, const GLchar* name)
	{
		this->Use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->UnUse();
	}

	void SetVector2f(glm::fvec2 value, const GLchar* name)
	{
		this->Use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UnUse();
	}

	void SetVector3f(glm::fvec3 value, const GLchar* name)
	{
		this->Use();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UnUse();
	}

	void SetVector4f(glm::fvec4 value, const GLchar* name)
	{
		this->Use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->UnUse();
	}

	void SetMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->Use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->UnUse();
	}

	void SetMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->Use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->UnUse();
	}
};