#include "Renderable2D.h"

Renderable2D::Renderable2D(const char* ID, Vec3 pos, Vec2 size, Vec4 col, GLuint shaderProg)
:  ShaderProgramID(shaderProg)
{
    UniqueID = ID;
    Position = pos;
    Size = size;
    Color = col;

    VAO = new VertexArray();

	GLfloat vertices[] = 
	{
		0, 0, 0,
		0, Size.y, 0, 
		Size.x, Size.y, 0,
		Size.x, 0, 0
	};

	GLfloat colors[] =
	{
		Color.x, Color.y, Color.z, Color.w,
		Color.x, Color.y, Color.z, Color.w,
		Color.x, Color.y, Color.z, Color.w,
		Color.x, Color.y, Color.z, Color.w
	};

    //Set specific shader info
	VAO->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	VAO->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

	GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
	IBO = new IndexBuffer(indices, 6);
}

Renderable2D::~Renderable2D()
{
    delete VAO;
    delete IBO;
}