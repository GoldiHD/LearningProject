#pragma once
#include<vector>
#include"Vertex.h"
#include<glew.h>
#include<glfw3.h>

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> inidices;

public:
	Primitive()	{}

	virtual ~Primitive() {}

	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->inidices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->inidices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->inidices.size(); }
};

class Quad : public Primitive
{
public:
	Quad() : Primitive()
	{
		Vertex vertices[] =
		{
			//Position						//Color						//Coord					//Normal
			glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f,0.f,1.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f,0.f,1.f)
		};

		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3		//Triangle 2
		};

		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Triangle : public Primitive
{
public:
	Triangle() : Primitive()
	{
		Vertex vertices[] =
		{
			//Position						//Color						//Coord					//Normal
			glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f,0.f,1.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f,0.f,1.f)
		};

		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
		};

		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};