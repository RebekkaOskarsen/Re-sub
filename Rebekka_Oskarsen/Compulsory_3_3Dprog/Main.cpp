#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Surface.h"
#include "Player.h"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT); 
void processInput(GLFWwindow* window); 

//Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
	glfwInit(); //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Compulsory 3", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD
	gladLoadGL();

	Shader shaderProgram("default.vert", "default.frag");

	Surface surface;

	Player player1;

	
	while (!glfwWindowShouldClose(window)) // Check if the window should close
	{
		//Calculate delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input
		processInput(window);

		//Render
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate the shader
		shaderProgram.Activate();


		//Camera/view transformation
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(-3.0f, -2.0f, -10.0f));
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");

		shaderProgram.SetMatrix4("model", model);
		shaderProgram.SetMatrix4("view", view);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		shaderProgram.SetMatrix4("projection", projection);

		//Render the surface
		surface.DrawSurface();

		//Render the player
		player1.DrawPlayer(shaderProgram.ID, view, projection);

		//Swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT)
{
	glViewport(0, 0, WIDTH, HEIGHT);
	std::cout << "Window resized with " << WIDTH << "Height" << HEIGHT << std::endl;
}