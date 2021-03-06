#include "libs.h"
#include <list>
#include "Game.h"
using namespace std;

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

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

GLFWwindow* createWindow(const char* title,const int width, const int height, int& fbWidth, int& fbHeight, int GLmajorVer, int GLminorVer, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	//glViewport(0, 0, framebufferWitdh, framebufferHeight);

	glfwMakeContextCurrent(window); //important
	return window;
}


int main()
{
	Game game("Buggers", 640, 480, 4, 5, false);
	//Seehader Init
	Shader core_program(GlmajorVersion,GLminorVersion,"vertex_core.glsl","fragment_core.glsl" );

	//MODEL MESH
	Mesh test(&Quad(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

	//TEXTURE INIT
	Texture texture0("Images/Parrying_Dagger.png",GL_TEXTURE_2D, 0);
	Texture texture1("Images/wallhaven-698267.png", GL_TEXTURE_2D, 1);

	//MATERIAL INIT
	Material material0(glm::vec3(0.1f),glm::vec3(1.f), glm::vec3(1.f),texture0.getTextureUnit(), texture1.getTextureUnit());

	//camera view matrix
	glm::vec3 camPostion(0.f, 0.f, 1.f);
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPostion, camPostion + camFront, worldUp);

	//CAMERA 
	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWitdh) / framebufferHeight, nearPlane, farPlane);

	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	//INIT UNIFORMS
	core_program.SetMat4fv(ViewMatrix, "ViewMatrix");
	core_program.SetMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.SetVector3f(lightPos0, "lightPos0");
	core_program.SetVector3f(camPostion, "cameraPos");

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Update input
		glfwPollEvents();
		updateInput(window, test);

		//UPDATE --- 
		updateInput(window);

		//DRAW ---
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Update uniforms
		core_program.Set1i(texture0.getTextureUnit(), "texture0");
		core_program.Set1i(texture1.getTextureUnit(), "texture1");
		material0.sendToShader(core_program);

		//Update framebuffer size and projectionMatrix
		glfwGetFramebufferSize(window, &framebufferWitdh, &framebufferHeight);
		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWitdh) / framebufferHeight, nearPlane, farPlane);
		core_program.SetMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//Use a program
		core_program.Use();
		
		//Active texture
		texture0.bind();
		texture1.bind();

		//Draw
		test.render(&core_program);

		//End Draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();



	return 0;
}