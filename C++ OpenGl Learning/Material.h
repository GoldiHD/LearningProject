#pragma once

#include "Shader.h"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	Material(glm::vec3 ambient,	glm::vec3 diffuse,	glm::vec3 specular,	GLint diffuseTex, GLint specularTex)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffuseTex = diffuseTex;
		this->specularTex = specularTex;
	}

	~Material()
	{

	}

	//Function
	void sendToShader(Shader& program)
	{
		program.SetVector3f(this->ambient, "material.ambient");
		program.SetVector3f(this->diffuse, "material.diffuse");
		program.SetVector3f(this->specular, "material.specular");
		program.Set1i(this->diffuseTex, "material.diffuseTex");
		program.Set1i(this->specularTex, "material.specularTex");
	}
};