#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player
{
public:
	Player();
	~Player();

	void MovePlayer(GLFWwindow* window, float deltaTime);

	void DrawPlayer(GLuint shaderProgram, glm::mat4 view, glm::mat4 projection);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !PLAYER_CLASS_H

