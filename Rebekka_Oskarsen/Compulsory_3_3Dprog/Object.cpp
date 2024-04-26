#include "Object.h"

Object::Object(float xOffset, float yOffset, float zOffset)
{
	VAO = 0;
	VBO = 0;
	EBO = 0;

	//Cube
	GLfloat objectvertices[] =
	{
		//positions   /		 colors //
		// Front face
	0.4f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Bottom-left 
	0.6f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Bottom-right 
	0.6f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-right 
	0.4f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-left 

	// Back face
	0.4f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left 
	0.6f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-right 
	0.6f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Top-right 
	0.4f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Top-left 

	// Top face
	0.6f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-right 
	0.4f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-left 
	0.6f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-right 
	0.4f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left 

	// Bottom face
	0.4f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-left 
	0.6f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-right 
	0.6f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-right 
	0.4f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left 

	// Right face
	0.6f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Bottom-right 
	0.6f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-right 
	0.6f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Top-left 
	0.6f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left 

	// Left face
	0.4f, 0.0f, -0.3f,    1.0f, 0.0f, 0.0f, // Bottom-left 
	0.4f, 0.2f, -0.3f,    1.0f, 0.0f, 0.0f, // Top-left 
	0.4f, 0.2f, -0.5f,   1.0f, 0.0f, 0.0f, // Top-right 
	0.4f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-right 
	};

	GLuint objectindices[] =
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

	//Position
	for (int i = 0; i < sizeof(objectvertices) / sizeof(float); i += 6)
	{
		objectvertices[i] += xOffset;
		objectvertices[i + 1] += yOffset;
		objectvertices[i + 2] += zOffset;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(objectvertices), objectvertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(objectindices), objectindices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Object::~Object()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Object::DrawObject()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
