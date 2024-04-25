#include "Player.h"

Player::Player()
{
    VBO = 0;
    VAO = 0;
    EBO = 0;

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

	memcpy(this->playervertices, playervertices, sizeof(playervertices));

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

	//Buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playervertices), playervertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerindices), playerindices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

}

Player::~Player()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Player::MovePlayer(GLFWwindow* window)
{
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

	// Bind VBO and upload updated vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playervertices), playervertices, GL_STATIC_DRAW);
	

}

void Player::DrawPlayer()
{

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
