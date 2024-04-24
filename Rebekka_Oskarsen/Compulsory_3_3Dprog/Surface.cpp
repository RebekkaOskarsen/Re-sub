#include "Surface.h"

Surface::Surface()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;


	GLfloat surfacevertices[] =
	{
		// positions        /	colors		   //
		//first square
		 1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top right			// 0
		 1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 0.0f, // bottom right		// 1
		-1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 0.0f, // bottom left		// 2
		-1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top left			// 3
		 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // middle			// 4

		 //second square
		 3.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top right			// 5
		 3.0f, 0.0f,  -1.0f,  1.0f, 1.0f, 0.0f,// bottom right		// 6
		 1.0f, 0.0f,  -1.0f,  1.0f, 1.0f, 0.0f,// bottom left		// 7
		 1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top left			// 8
		 2.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // middle			// 9

		 //third square
		 5.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top right			// 10
		 5.0f, 0.0f,  -1.0f,  1.0f, 1.0f, 0.0f,// bottom right		// 11
		 3.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f,// bottom left		// 12
		 3.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top left			// 13
		 4.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // middle			// 14

		 //fourth square
		 7.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top right			// 15
		 7.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f,// bottom right		// 16
		 5.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f,// bottom left		// 17
		 5.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // top left			// 18
		 6.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // middle			// 19

		 //fifth square
		 1.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top right		// 20
		 1.0f, 0.0f,  -3.0f,  1.0f, 1.0f, 0.0f, // bottom right		// 21
		 -1.0f, 0.0f,  -3.0f,  0.0f, 1.0f, 0.0f,// bottom left		// 22
		 -1.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f,// top left			// 23
		 0.0f, 1.0f,  -2.0f,  0.0f, 1.0f, 0.0f, // middle			// 24

		 //sixth square
		 3.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top right		// 25
		 3.0f, 0.0f,  -3.0f,  1.0f, 1.0f, 0.0f, // bottom right		// 26
		 1.0f, 0.0f,  -3.0f,  0.0f, 1.0f, 0.0f, // bottom left		// 27
		 1.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top left			// 28
		 2.0f, 1.0f,  -2.0f,  0.0f, 1.0f, 0.0f, // middle			// 29

		 //seventh square
		 5.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top right		// 30
		 5.0f, 0.0f,  -3.0f,  1.0f, 1.0f, 0.0f, // bottom right		// 31
		 3.0f, 0.0f,  -3.0f,  1.0f, 1.0f, 0.0f, // bottom left		// 32
		 3.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top left			// 33
		 4.0f, 1.0f,  -2.0f,  0.0f, 1.0f, 0.0f, // middle			// 34

		 //eighth square
		 7.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, // top right		// 35
		 7.0f, 0.0f,  -3.0f,  0.0f, 1.0f, 0.0f, // bottom right		// 36
		 5.0f, 0.0f,  -3.0f,  1.0f, 1.0f, 0.0f, // bottom left		// 37
		 5.0f, 0.0f,  -1.0f,  1.0f, 1.0f, 0.0f, // top left			// 38
		 6.0f, 1.0f,  -2.0f,  0.0f, 1.0f, 0.0f // middle			// 39

	};

	GLuint surfaceindices[] =
	{
		//first square
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,

		//second square
		5, 6, 9,
		1, 6, 9,
		0, 5, 9,
		1, 0, 9,

		//third square
		5,10,14,
		10,11,14,
		11,6,14,
		6,5,14,

		//fourth square
		10,15,19,
		15,16,19,
		16,11,19,
		11,10,19,
		
		//fifth square
		1,21,24,
		21,22,24,
		22,2,24,
		2,1,24,

		//sixth square
		6,26,29,
		26,27,29,
		21,7,29,
		1,6,29,

		//seventh square
		11,31,34,
		31,26,34,
		26,6,34,
		6,11,34,

		//eighth square
		16,36,39,
		36,31,39,
		31,11,39,
		11,16,39,

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(surfacevertices), surfacevertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(surfaceindices), surfaceindices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw in wireframe
}

Surface::~Surface()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Surface::DrawSurface()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
