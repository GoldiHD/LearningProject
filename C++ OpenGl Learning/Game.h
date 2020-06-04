#pragma once
#include"libs.h"

class Game
{
private:
//Variables
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

//Private Functions
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW();//AFTER CONTEXT IS CREATED
	void initOpenGLOptions();
	void initMatrices();

//Static variables

public:
	//Constructors/Destructors
	Game(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable);
	virtual ~Game();

	//Accessors
	int getWindowShouldClose();

	//Modifiers
	void setWindowShouldClose();

	//Functions
	void updateInput(GLFWwindow* window, Mesh& mesh)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(0.f, 0.01f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(0.f, -0.01f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(-0.01f, 0.f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(0.01f, 0.f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(0.f, 0.f, 0.01f));
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			mesh.Move(glm::vec3(0.f, 0.f, -0.01f));
		}

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			mesh.Rotate(glm::vec3(0.f, -1.f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			mesh.Rotate(glm::vec3(0.f, 1.f, 0.f));
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			mesh.Scale(glm::vec3(0.01f));
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			mesh.Scale(glm::vec3(-0.01f));
		}
	}

	void update();
	void render();

	//Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};

