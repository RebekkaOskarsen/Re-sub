#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Object
{
public:
	Object(float xOffset, float yOffset, float zOffset);
	~Object();

	void DrawObject();

private:
	GLuint VAO, VBO, EBO;
};
#endif // !OBJECT_H

