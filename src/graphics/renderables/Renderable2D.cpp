#include "Renderable2D.h"

Renderable2D::Renderable2D(const char *in_ID, Vec3f pos, Vec2f size, Vec4f col, GLuint shaderProg)
	: ShaderProgramID(shaderProg), ID(in_ID)
{
}

Renderable2D::~Renderable2D()
{
	delete VAO;
	delete IBO;
}

void Renderable2D::LoadTexture(const char *inImagePath)
{
	tex->imagePath = inImagePath;
	LOG_INF("Genning tex\n");

	if (wglGetCurrentContext() == NULL)
	{
		LOG_ERR("NO CONTEXT WHILE GENNING TEXTURE!\n");
	}

	glGenTextures(1, tex->texture);
	LOG_INF("Gennd tex\n");
	glBindTexture(GL_TEXTURE_2D, *(tex->texture));
	LOG_INF("Tex bound\n");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LOG_INF("Extracting image information from: %s\n", tex->imagePath);
	unsigned char *data = SOIL_load_image(tex->imagePath, tex->width, tex->height, 0, SOIL_LOAD_RGB);
	LOG_INF("SHIIIT\n");
	if (data)
	{
		LOG_INF("Before glTexImage\n");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *(tex->width), *(tex->height), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		LOG_INF("Generating mipmaps\n");
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_WRN("Failed to load texture.");
	}
	LOG_INF("Freeing image data.\n");
	SOIL_free_image_data(data);
	LOG_INF("Texture loaded\n");
}