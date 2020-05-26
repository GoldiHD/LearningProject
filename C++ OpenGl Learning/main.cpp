#include "libs.h"
#include <list>
using namespace std;

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

bool loadShader(GLuint& program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;


	//vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}


	//Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}


void updateInput(GLFWwindow* window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.01f,0.f));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, -0.01f, 0.f));
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.Rotate(glm::vec3(0.f, 1.f, 0.f));
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.Rotate(glm::vec3(0.f, -1.f, 0.f));
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.scale()
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		scale -= 0.1f;
	}
}


int main()
{
	//init GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	int framebufferWitdh = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Buggers", NULL, NULL);

	glfwGetFramebufferSize(window, &framebufferWitdh, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	//glViewport(0, 0, framebufferWitdh, framebufferHeight);

	glfwMakeContextCurrent(window); //important

	//INIT GLEW (NEEDS WINDOW AND OPTION CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR´::MAIN.cpp::GLEN_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Shader Init
	Shader core_program("vertex_core.glsl","fragment_core.glsl" );

	//MODEL MESH
	Mesh test(vertices, nrOfVertices, indices, nrOfIndices, glm::vec3(0.f), glm::vec3(10.f), glm::vec3(1.f));

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
		updateInput(window, position, rotation, scale);

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

		//Move, rotate, scalling

		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.SetMat4fv(ModelMatrix, "ModelMatrix");
		glfwGetFramebufferSize(window, &framebufferWitdh, &framebufferHeight);
		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWitdh) / framebufferHeight, nearPlane, farPlane);
		core_program.SetMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//Use a program
		core_program.Use();
		
		//Active texture
		texture0.bind();
		texture1.bind();

		//Bind vertex array object
		glBindVertexArray(VAO);

		//Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfIndices);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);
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