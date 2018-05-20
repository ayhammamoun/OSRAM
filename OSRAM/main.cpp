#include "src/graphics/Window.h"
#include "src/input/Input.h"
#include "src/graphics/Shaders.h"
#include "src/graphics/buffer/VBO.h"
#include "src/graphics/buffer/IBO.h"
#include "src/graphics/buffer/VAO.h"
#include "src/graphics/Spirite2D.h"
#include "src/graphics/MVP.h"
#include "src/audio/AudioManager.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/mat4x4.hpp>
#include <iostream>

void draw_vbo()
{
	GLuint vbo, ibo;
	GLfloat vert[8] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f
	};
	GLubyte ind[6] = { 0,1,2, 3,1,2 };

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(GLubyte), ind,
		GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

int main()
{
	GLfloat vert[8] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f
	};
	GLubyte ind[6] = { 0,1,2, 3,1,2 };

	OSRAM::GRAPHICS::Window window(460, 460, "Defualt Title");
	OSRAM::INPUT::Input input(window.getWindowHandler(), GLFW_CURSOR_NORMAL);
	OSRAM::GRAPHICS::Shaders shader;
	OSRAM::GRAPHICS::MVP mvp(&shader);
	//OSRAM::GRAPHICS::BUFFER::VBO vbo(vert, 8, 2);
	//OSRAM::GRAPHICS::BUFFER::IBO ibo(ind, 6);
	
	glm::mat4 proj(1.0f);
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.4f, 0.3f));
	view = glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	OSRAM::GRAPHICS::Spirite2D::DATA data;
	data._center = glm::vec2(0.0f, 0.0f);
	data._size = glm::vec2(0.5f, 0.5f);
	data._color[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
	data._color[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
	data._color[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
	data._color[3] = glm::vec4(0.5f, 0.5f, 0.0f, 0.5f);

	OSRAM::GRAPHICS::Spirite2D sprite(data, &shader);
	shader.UseBasicProgram();
	//shader.Uniform4f(shader.GetBasicProgram(),"m_Color", 0.2f, 0.3f, 0.5f, 1.0f);
	//glClearColor(0.03f, 0.0f, 0.0f, 1.0f);

	OSRAM::AUDIO::AudioManager audio;

	audio.DisplayDeviceList();

	audio.AddScene("main");
	audio.AddAudioObject(audio.GetSceneID("main"), "test1", 1, glm::vec3(0, 0, 0), 1, true, glm::vec3(0, 0, 0));
	audio.RemoveAudioObject(audio.GetSceneID("main"), "test1");

	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();
		window.RenderImGUI();
		mvp.SetViewMatrix(view);
		sprite.LegacyDraw();
	}
	return 0;
}