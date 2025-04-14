#include <iostream>
#include "glad.h"
#include "glfw3.h"
#include "shader.hpp"
#include "bmp.hpp"


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
	float vertices[]{
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};

	unsigned int indices[]{
		0, 1, 2
	}; // First Triangle


	// -- Vertex Shader
	Shader solidColorShader("../res/shaders/basic.vert", "../res/shaders/screenPos.frag");
	
	// Create OpenGL Objects
	// -- Vertex Buffer
	unsigned int VBO[1];
	glGenBuffers(1, VBO);

	// -- Vertex Array
	unsigned int VAO[1];
	glGenVertexArrays(1, VAO);

	// -- Element Buffer
	unsigned int EBO[1];
	glGenBuffers(1, EBO);

	// Bind the buffer while the array is bound
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// Load Texture
	BMP newTexture = BMP(1, 1, 1);
	unsigned char* a = newTexture.load("../res/textures/3x3random.bmp");
	std::cout << std::hex << a[0] << a[1] << a[10];
	newTexture.free(a);

	// Start Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Process Input
		processInput(window);

		// Render Logic
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state setting function
		glClear(GL_COLOR_BUFFER_BIT);

		// Time Green Shader Uniform Setting
		float timeValue = (float) glfwGetTime();
		float greenValue = sin(timeValue)/2.0f + 0.5f;

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		solidColorShader.use();
		solidColorShader.setVec2("resolution", (float) width, (float) height);
	
		// Render Right Tri
		//glUseProgram(shaderProgram2); 
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
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
