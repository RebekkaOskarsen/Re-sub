#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Surface.h"
#include "Object.h"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
void processInput(GLFWwindow* window);

//Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


//Cube
GLfloat playervertices[] =
{
	//positions   /		 colors //
	// Front face
   0.2f, 0.0f, 0.1f,    0.0f, 0.0f, 1.0f, // Bottom-left
	0.4f, 0.0f, 0.1f,    0.0f, 0.0f, 1.0f, // Bottom-right
	0.4f, 0.2f, 0.1f,    0.0f, 0.0f, 1.0f, // Top-right
	0.2f, 0.2f, 0.1f,    0.0f, 0.0f, 1.0f, // Top-left

	// Back face
	0.2f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-left
	0.4f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-right
	0.4f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Top-right
	0.2f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Top-left

	// Top face
	0.4f, 0.2f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-right
	0.2f, 0.2f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-left
	0.4f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-right
	0.2f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-left

	// Bottom face
	0.2f, 0.0f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-left
	0.4f, 0.0f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-right
	0.4f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-right
	0.2f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-left

	// Right face
	0.4f, 0.0f, 0.1f,   0.0f, 0.0f, 1.0f, // Bottom-right
	0.4f, 0.2f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-right
	0.4f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Top-left
	0.4f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-left

	// Left face
	0.2f, 0.0f, 0.1f,   0.0f, 0.0f, 1.0f, // Bottom-left
	0.2f, 0.2f, 0.1f,   0.0f, 0.0f, 1.0f, // Top-left
	0.2f, 0.2f, -0.1f,   0.0f, 0.0f, 1.0f, // Top-right
	0.2f, 0.0f, -0.1f,   0.0f, 0.0f, 1.0f, // Bottom-right
};

GLuint playerindices[] =
{
	// Front face
	0, 1, 2,
	2, 3, 0,

	// Back face
	4, 5, 6,
	6, 7, 4,

	// Top face
	8, 9, 10,
	10, 11, 8,

	// Bottom face
	12, 13, 14,
	14, 15, 12,

	// Right face
	16, 17, 18,
	18, 19, 16,

	// Left face
	20, 21, 22,
	22, 23, 20

};


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

	Object object1(0.0f, 0.0f, 0.0f); //Position at origin
	Object object2(2.0f, 0.0f, 0.0f);
	Object object3(1.0f, 0.0f, -2.0f); 

	//Buffers/arrays
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playervertices), playervertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerindices), playerindices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);

	float distanceFromPlayer = 3.0f; //Adjust this value to change the distance from player
	glm::vec3 cameraPosOffset = glm::vec3(0.0f, 0.0f, 1.0f); //Offset behind the player to maintain a consistent height

	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
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

		// Calculate the target position for the camera (behind the player)
		glm::vec3 targetPos = glm::vec3(playervertices[0], playervertices[1], playervertices[2]);

		targetPos.y += 1.0f;

		// Calculate the new position for the camera
		glm::vec3 cameraPos = targetPos - glm::normalize(cameraFront) * distanceFromPlayer;

		// Adjust the camera position to maintain a consistent height above the surface
		cameraPos.y = cameraPosOffset.y; // Set the camera to a consistent height above the player

		// Adjust the camera position to maintain a consistent distance from the player
		cameraPos -= glm::normalize(cameraFront) * distanceFromPlayer;

		model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(-3.0f, -2.0f, -10.0f));
		view = glm::lookAt(cameraPos, targetPos, cameraUp);
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

		//Render the object
		object1.DrawObject();
		object2.DrawObject();
		object3.DrawObject();

		//Render the player
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		//Swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

glm::vec3 playerPosition(0.0f);


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Player movement controls
	const float playerSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		for (int i = 2; i < 144; i += 6)
			playervertices[i] -= playerSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		for (int i = 2; i < 144; i += 6)
			playervertices[i] += playerSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		for (int i = 0; i < 144; i += 6)
			playervertices[i] -= playerSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		for (int i = 0; i < 144; i += 6)
			playervertices[i] += playerSpeed;
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(playervertices), playervertices, GL_STATIC_DRAW);
}

void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT)
{
	glViewport(0, 0, WIDTH, HEIGHT);
	std::cout << "Window resized with " << WIDTH << "Height" << HEIGHT << std::endl;
}