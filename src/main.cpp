#include <iostream>
#include <glad.h>
#include "glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	std::cout << "Hello World!\n";

	// Hint to GLFW we are going to be using OpenGL 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Make GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLVR", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Tell OpenGL Viewport Size
	glViewport(0, 0, 800, 600);

	// Set Callback for resizing OpenGL viewport when GLFW size adjusted
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Create Resources
	// -- Vertex Data
	float vertices[] {			
		-0.5f, -0.5f, 0.0f,		// Bottom Left
		0.5f, -0.5f, 0.0f,		// Bottom Right
		0.5f, 0.5f, 0.0f,		// Top Right
		-0.5f, 0.5f, 0.0f,		// Top Left
	};

	unsigned int indices[] {
		0, 1, 2,	// First Triangle
		2, 3, 0		// Second Triangle
	};

	// -- Vertex Shader
	const char* vertexShaderSrc = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main(){\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\0";

	// -- Fragment Shader
	const char* fragmentShaderSrc = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
		"}\n";


	// Compile Shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	// Check Shader Compilation
	int success;
	char infoLog[512];

	// -- Vertex Checking ERROR_S1
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR_S1: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
	}

	// -- Frag Checking ERROR_S2
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR_S2: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
	}


	// Create OpenGL Objects
	// -- Vertex Buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// -- Vertex Array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// -- Element Buffer
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Bind the buffer while the array is bound
	// -- VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// -- EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// -- Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Checker Shader Program Linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR_S3: Shader Linking Failed\n" << infoLog << std::endl;
	}

	// Link Shader and Free Resources
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);


	// Start Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Process Input
		processInput(window);

		// Render Logic
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // state setting function
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Render
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean Resources
	glfwTerminate();
	return 0;
}

// Function callback to resize OpenGL viewport when GLFW window size adjusted
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Function to process inputs
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}