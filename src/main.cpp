#include <iostream>
#include <glad.h>
#include "glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	std::cout << "Hello World!";

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

	// Start Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Process Input
		processInput(window);

		// Render Logic
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // state setting function
		glClear(GL_COLOR_BUFFER_BIT);

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