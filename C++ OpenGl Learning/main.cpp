#include "libs.h"

Vertex vertices[] =
{
	//Position						//Color
	glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.f, 1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.f, 0.f),
	glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f,0.f,1.f),		glm::vec2(1.f, 0.f),
	glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f, 0.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 2,	
	0,1,3		
};

unsigned nrOfIndices = sizeof(indices) / sizeof(Vertex);


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


int main()
{
	//init GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWitdh = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Buggers", NULL, NULL);

	glfwGetFramebufferSize(window, &framebufferWitdh, &framebufferHeight);
	glViewport(0, 0, framebufferWitdh, framebufferHeight);

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
	GLuint core_program;
	if (!loadShader(core_program))
	{
		glfwTerminate();
	}

	//Model


	//VBO, VBO, ERO
	//GEN VAD AND BIND
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);




	//GEN VBO AND BIND AND SEND DATA
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//GEN EBO AND BIND AND SEND DATA
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//SET VERTEXATTRIBPOINTERS AND ENABLE (Input ASSEMBLY)
		//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
		//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
		//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//BIND VAO 0
	glBindVertexArray(0);

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Update input
		glfwPollEvents();

		//UPDATE --- 
		updateInput(window);

		//DRAW ---
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Use a program
		glUseProgram(core_program);

		//Bind vertex array object
		glBindVertexArray(VAO);

		//Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfVertices, GL_UNSIGNED_INT, 0);

		//End Draw
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}