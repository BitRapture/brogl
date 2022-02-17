#pragma once

#include <STB/image.h>
#include <stdexcept>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <cmath>

#include "texturing.h"

void texturing::Run(SDL_Window* _window)
{
	// Clear buffer with solid color
	glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind shader and VAO
	glUseProgram(shader.id);
	glBindVertexArray(quad.id);

	// Bind element indices and texture to sample0
	glBindBuffer(inds.type, inds.id);
	glBindTexture(quadTex.type, quadTex.id);

	// Prepare perspective projection matrix
	float w, h;
	SDL_GetWindowSize(_window, (int*)&w, (int*)&h);
	glm::mat4 projection = glm::perspective(glm::radians(45.f), w / h, 0.1f, 100.f);

	// Prepare model matrices
	glm::mat4 model(1.f);
	model = glm::translate(model, glm::vec3(sinf(angle / 200) * 0.5f, sinf(angle / 100), (sinf(angle / 50) *2) + -10.5f));
	model = glm::rotate(model, glm::radians((angle += 0.8f) / 1.5f), glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 modelb(1.f);
	modelb = glm::translate(modelb, glm::vec3(sinf(angle / 100), sinf(angle / 200), (sinf(angle / 500) * 4) + -5.5f));
	modelb = glm::rotate(modelb, glm::radians(angle / 10.f), glm::vec3(0.f, 1.f, 0.f));

	// Upload matrices to respective uniforms
	glUniformMatrix4fv(shader.uniforms["uProjection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(shader.uniforms["uModel"], 1, GL_FALSE, glm::value_ptr(model));

	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	// Draw second quad
	glUniformMatrix4fv(shader.uniforms["uModel"], 1, GL_FALSE, glm::value_ptr(modelb));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	// Unbind everything
	glBindTexture(quadTex.type, 0);
	glBindBuffer(inds.type, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

texturing::texturing()
{
	// Require vsync
	if (SDL_GL_SetSwapInterval(1) == -1) { throw std::runtime_error("No vertical sync"); };

	// Get vertex positions to add to VBO
	const GLfloat verts[]{
		-0.8f, 0.8f, 0.0f,
		0.8f, 0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f
	};
	vertices = bro::CreateVBO(sizeof(verts), verts, GL_STATIC_DRAW);
	bro::attribparams vertAttribs = { { "aPosition", 3, GL_FLOAT } };

	// Get vertex indices to add to VBO
	indices.insert(indices.begin(), { 0, 2, 3, 0, 1, 2 });
	inds = bro::CreateVBO(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	// Get texture coords to add to VBO
	const GLfloat texcoords[]{
		0.0f, 0.0f, 
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	texCoords = bro::CreateVBO(sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	bro::attribparams texAttribs = { { "aTexCoord", 2, GL_FLOAT } };

	// Add positions and texture coords to VAO
	quad = bro::CreateVAO({ {vertices, vertAttribs}, {texCoords, texAttribs} });

	// Compile and link shaders
	bro::shadersources shaderRes{
		{ GL_VERTEX_SHADER, bro::ReadFile("./src/examples/texturing/shader.vert") },
		{ GL_FRAGMENT_SHADER, bro::ReadFile("./src/examples/texturing/shader.frag") }
	};
	bro::shaderpack shaderComp = bro::CompileShaders(shaderRes);
	shader = bro::LinkShaders(shaderComp, { { "uTex", "uModel", "uProjection" }, quad.attributes });
	bro::DeleteShaderpack(shaderComp);

	// Open and save texture image data
	int w{ 0 }, h{ 0 };
	unsigned char* data = stbi_load("./src/res/hm3.png", &w, &h, NULL, STBI_rgb_alpha);
	if (!data) { throw std::runtime_error("Texture data failed to load"); }
	quadTex = bro::CreateTexture2D(data, w, h); delete[] data;

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Enable back face culling
	//glEnable(GL_CULL_FACE);
}

texturing::~texturing()
{
	
}