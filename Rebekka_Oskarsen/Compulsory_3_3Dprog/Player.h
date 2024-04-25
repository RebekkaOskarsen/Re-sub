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

	void MovePlayer(GLFWwindow* window);
	void DrawPlayer();

	float deltaTime = 0.0f;	// time between current frame and last frame

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLfloat playervertices[144];
};

#endif // !PLAYER_CLASS_H

