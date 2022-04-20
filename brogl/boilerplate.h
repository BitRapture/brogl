/// Boilerplate code for setting up opengl and SDL2
#ifndef _BOILERPLATE_H_
#define _BOILERPLATE_H_

// Local dependencies
#include "defs.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>

// STL dependencies
#include <vector>
#include <stdexcept>

namespace bro
{
	/// @brief Initialize the opengl context. Create an SDL2 window for opengl and initialize glew 
	/// @param _title Window title
	/// @param _x Window screen position x
	/// @param _y Window screen position y
	/// @param _width Window screen width
	/// @param _height Window screen height
	/// @param _flags Additional flags (OPENGL and RESIZABLE are enabled by default)
	/// @return The handle to the window context, throws on errors
	SDL_Window* InitializeContext(const char* _title, int _x, int _y, int _width, int _height, Uint32 _flags = 0);

	/// @brief Compiles a vector of shadersources
	/// @param _sources Shaders to be compiled into a shaderpack
	/// @return Shaderpack of the compiled shaders
	shaderpack CompileShaders(const shadersources& _sources);

	/// @brief Link a shaderpack together into a program
	/// @param _pack Shaderpack to link
	/// @param _extract Shader variables to be extracted
	/// @return Shaderprogram of the linked shaders
	shaderprogram LinkShaders(const shaderpack& _pack, const shaderextract& _extract);

	/// @brief Delete all shaders from a shaderpack
	/// @param _pack Shaderpack to delete
	void DeleteShaderpack(const shaderpack& _pack);

	/// @brief Create a VBO and bind it to data
	/// @param _size Size in bytes of the buffer's data
	/// @param _data Pointer to the data
	/// @param _usage Expected usage of the data
	/// @param _target The target buffer object
	/// @return Handle and id of the newly created vbo
	vbo CreateVBO(GLsizeiptr _size, const GLvoid* _data, GLenum _usage = GL_DYNAMIC_DRAW, GLenum _target = GL_ARRAY_BUFFER);

	/// @brief Update the buffer data within the vbo
	/// @param _vbo VBO to update
	/// @param _size Size in bytes of the buffer's data
	/// @param _data Pointer to the data
	/// @param _usage Expected usage of the data
	void UpdateVBOData(const vbo& _vbo, GLsizeiptr _size, const GLvoid* _data, GLenum _usage = GL_DYNAMIC_DRAW);

	/// @brief Create an empty vertex array object
	/// @return Handle to the vao and connected attributes
	vao CreateVAO(const vaoparams& _params);

	/// @brief Create a 2D texture
	/// @param _data Pixel data to be processed into a texture
	/// @param _width Width of the texture
	/// @param _height Height of the texture
	/// @param _internalformat Format opengl will use to store the texture data internally
	/// @param _format Format of the pixel data to be processed
	/// @param _target The target texture object
	/// @param _type Data type of the pixel data
	/// @param _level The level of detail
	/// @return Handle to the texture
	texture CreateTexture2D(const void* _data, GLsizei _width, GLsizei _height, GLint _internalformat = GL_RGBA,
		GLenum _format = GL_RGBA, GLenum _target = GL_TEXTURE_2D, GLenum _type = GL_UNSIGNED_BYTE, GLint _level = 0);

	/// @brief Create an attribute parameter for parsing 3D variables
	/// @param _name Attribute name
	/// @param _dataType Data type of the attribute
	/// @return Filled out attribute parameter struct
	attribparam CreateAttrib3D(std::string _name, GLenum _dataType);

	/// @brief Create an attribute parameter for parsing 2D variables
	/// @param _name Attribute name
	/// @param _dataType Data type of the attribute
	/// @return Filled out attribute parameter struct
	attribparam CreateAttrib2D(std::string _name, GLenum _dataType);

	/// @brief Create a VAO parameter, bind attributes to one vbo
	/// @param _vbo Handle to the vbo
	/// @param _attribs Attributes to bind to the vbo
	/// @return Filled out vao parameter struct
	vaoparam CreateVAOparam(vbo& _vbo, const attribparams& _attribs);
}

#endif // !_BOILERPLATE_H_
