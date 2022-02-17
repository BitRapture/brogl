/// Definitions for structures and types that brogl uses
#ifndef _DEFS_H_
#define _DEFS_H_

// External dependencies
#include <GLEW/glew.h>

// STL dependencies
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace bro
{
	/// @brief Shader source information to be compiled
	struct shadersource
	{
		// Shader type
		GLenum type;
		// Shader code source
		std::string source;

	};
	/// @brief Shader sources to be compiled into a shaderpack
	typedef std::vector<shadersource> shadersources;

	/// @brief VBO attribute
	struct attrib
	{
		// Attribute index
		GLuint index;
		// Attribute name
		std::string name;
	};
	/// @brief VBO attributes
	typedef std::vector<attrib> attribs;

	/// @brief Variables to extract after shaderprogram compilation
	struct shaderextract
	{
		// List of uniforms to extract
		const std::vector<std::string>& uniforms;
		// List of attributes to extract
		const attribs& attributes;
	};

	/// @brief Handle to a gl object
	struct glhandle
	{
		// Handle type
		GLenum type;
		// Handle compilation id
		GLuint id{ 0 };
	};
	/// @brief Handle to a vertex buffer object
	typedef glhandle vbo;
	/// @brief Handle to a shader
	typedef glhandle shader;
	/// @brief Handles to compiled shaders
	typedef std::vector<shader> shaderpack;
	/// @brief Handle to a texture
	typedef glhandle texture;

	/// @brief Program of linked shaders
	struct shaderprogram
	{
		// Unordered map of all uniforms 
		std::unordered_map<std::string, GLint> uniforms;
		// Shader program link id
		GLuint id{ 0 };
	};

	/// @brief Attribute parameters for VAO binding
	struct attribparam
	{
		// Attribute name
		std::string name;
		// Attribute size per vertex attribute
		GLint size;
		// Attribute type
		GLenum type;
		// Stride to the next element
		GLsizei stride{ 0 };
		// Offset for the first component of the attribute within VBO
		const GLvoid* pointer{ 0 };
		// Normalised
		GLboolean norm{ GL_FALSE };
	};
	/// @brief Attribute parameters for VAO binding
	typedef std::vector<attribparam> attribparams;

	/// @brief VAO parameter for VAO binding/creation
	struct vaoparam
	{
		// VBO to be binded
		const vbo& vbo;
		// VBO's attributes
		const attribparams& attribs;
	};
	/// @brief VAO parameters for VAO binding/creation 
	typedef std::vector<vaoparam> vaoparams;

	/// @brief Handle to a created VAO
	struct vao
	{
		// All binded attributes
		attribs attributes;
		// VAO id
		GLuint id{ 0 };
	};
}

#endif // !_DEFS_H_

