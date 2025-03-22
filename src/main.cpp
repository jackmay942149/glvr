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

	// OpenGL Information Requesting
	// -- number of supported vertex attributes (16 for my laptop, that is the minimum)
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;


	// Create Resources
	// -- Vertex Data
	float vertices1[]{
		0.1f, 0.0f, 0.0f,
		0.3f, 0.0f, 0.0f,
		0.2f, 0.2f, 0.0f
	};

	float vertices2[] {
		-0.1f, 0.0f, 0.0f,
		-0.3f, 0.0f, 0.0f,
		-0.2f, 0.2f, 0.0f,
	};

	unsigned int indices1[]{
		0, 1, 2
	}; // First Triangle

	unsigned int indices2[]{
		0, 1, 2		// Second Triangle
	};

	// -- Vertex Shader
	const char* vertexShaderSrc = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main(){\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\0";

	// -- Fragment Shader
	const char* fragmentShaderSrc1 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
		"}\n";

	// -- Fragment Shader
	const char* fragmentShaderSrc2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n";


	// Compile Shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader1;
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSrc1, NULL);
	glCompileShader(fragmentShader1);

	unsigned int fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSrc2, NULL);
	glCompileShader(fragmentShader2);

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
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR_S2: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "ERROR_S2: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
	}


	// Create OpenGL Objects
	// -- Vertex Buffer
	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	// -- Vertex Array
	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);

	// -- Element Buffer
	unsigned int EBO[2];
	glGenBuffers(2, EBO);

	// Bind the buffer while the array is bound
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0); // Dont need to do this explicitly

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0); // Dont need to do this explicitly

	// -- Shader Program
	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	// Checker Shader Program Linking
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success) {
		glad_glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
		std::cout << "ERROR_S3: Shader Linking Failed\n" << infoLog << std::endl;
	}

	// -- Shader Program
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	// Checker Shader Program Linking
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glad_glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "ERROR_S3: Shader Linking Failed\n" << infoLog << std::endl;
	}

	// Link Shader and Free Resources
	glUseProgram(shaderProgram1);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);

	

	// Start Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Process Input
		processInput(window);

		// Render Logic
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // state setting function
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
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