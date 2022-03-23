#pragma once

// Link to header
#include "../boilerplate.h"
namespace bro
{
	SDL_Window* InitializeContext(const char* _title, int _x, int _y, int _width, int _height, Uint32 _flags)
	{
		// Create SDL window
		SDL_Window* window = SDL_CreateWindow(_title, _x, _y, _width, _height, _flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		// Initialize glew and gl context
		if (!SDL_GL_CreateContext(window) || glewInit() != GLEW_OK) { throw std::runtime_error("Context failed to initialize"); }
		return window;
	}

	shaderpack CompileShaders(const shadersources& _sources)
	{
		// Create new shaderpack
		shaderpack sp;
		// Compile every shadersource
		GLint success = 0;
		for (const shadersource& s : _sources)
		{
			// Create shader
			GLuint shaderId = glCreateShader(s.type);
			const char* source = s.source.c_str();
			// Compile source
			glShaderSource(shaderId, 1, &source, NULL);
			glCompileShader(shaderId);
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
			if (!success) { throw std::runtime_error("Shader compilation failed"); }
			// Add to shaderpack
			sp.push_back({ s.type, shaderId });
		}
		return sp;
	}

	shaderprogram LinkShaders(const shaderpack& _pack, const shaderextract& _extract)
	{
		// Create new shaderprogram
		shaderprogram sp;
		sp.id = glCreateProgram();
		// Attach every shader
		for (const shader& s : _pack) { glAttachShader(sp.id, s.id); }
		// Attach attributes
		for (const attrib& a : _extract.attributes)
		{
			glBindAttribLocation(sp.id, a.index, a.name.c_str());
		}
		// Link all shaders together
		glLinkProgram(sp.id);
		// Check for errors
		GLint success = 0;
		glGetProgramiv(sp.id, GL_LINK_STATUS, &success);
		if (!success) { throw std::runtime_error("Shader linking failed"); }
		// Detach every shader
		for (const shader& s : _pack) { glDetachShader(sp.id, s.id); }
		// Add uniforms 
		for (const std::string& e : _extract.uniforms)
		{
			GLint uniform = glGetUniformLocation(sp.id, e.c_str());
			if (uniform == -1) { success = 0; break; }
			sp.uniforms[e] = uniform;
		}
		if (!success) { throw std::runtime_error("Uniform extraction failed"); }
		return sp;
	}

	void DeleteShaderpack(const shaderpack& _pack)
	{
		// Delete every shader
		for (const shader& s : _pack) { glDeleteShader(s.id); }
	}

	vbo CreateVBO(GLsizeiptr _size, const GLvoid* _data, GLenum _usage, GLenum _target)
	{
		// Generate 1 new buffer
		vbo v; v.type = _target;
		glGenBuffers(1, &v.id);
		if (!v.id) { throw std::runtime_error("VBO generation failed"); }
		// Bind to new buffer
		glBindBuffer(_target, v.id);
		// Add data
		glBufferData(_target, _size, _data, _usage);
		// Unbind buffer
		glBindBuffer(_target, 0);
		return v;
	}

	void UpdateVBOData(const vbo& _vbo, GLsizeiptr _size, const GLvoid* _data, GLenum _usage)
	{
		glBindBuffer(_vbo.type, _vbo.id);
		glBufferData(_vbo.type, _size, _data, _usage);
		glBindBuffer(_vbo.type, 0);
	}

	vao CreateVAO(const vaoparams& _params)
	{
		// Generate 1 new vertex array
		vao v; 
		glGenVertexArrays(1, &v.id);
		if (!v.id) { throw std::runtime_error("VAO generation failed"); }
		// Bind to new vao
		glBindVertexArray(v.id);
		// Loop through all params
		GLuint index = 0;
		for (const vaoparam& vp : _params)
		{
			glBindBuffer(vp.vbo.type, vp.vbo.id);
			for (const attribparam& ap : vp.attribs)
			{
				// Add attributes to the vao for each vbo
				glVertexAttribPointer(index, ap.size, ap.type, ap.norm, ap.stride, ap.pointer);
				v.attributes.push_back({ index, ap.name });
				glEnableVertexAttribArray(index++);
			}
			// Unbind from buffer
			glBindBuffer(vp.vbo.type, 0);
		}
		// Unbind vertex array
		glBindVertexArray(0);
		return v;
	}

	texture CreateTexture2D(const void* _data, GLsizei _width, GLsizei _height, GLint _internalformat, 
		GLenum _format, GLenum _target, GLenum _type, GLint _level)
	{
		texture t; t.type = _target;
		glGenTextures(1, &t.id);
		if (!t.id) { throw std::runtime_error("Texture generation failed"); }
		// Bind to new texture
		glBindTexture(_target, t.id);
		// Create texture from pixel data
		glTexImage2D(_target, _level, _internalformat, _width, _height, 0, _format, _type, _data);
		// Generate mipmap for texture (might separate for memory)
		glGenerateMipmap(_target);
		// Unbind from texture
		glBindTexture(_target, 0);
		return t;
	}

	attribparam CreateAttrib3D(std::string _name, GLenum _dataType)
	{
		attribparam a{ _name, 3, _dataType };
		return a;
	}

	vaoparam CreateVAOparam(vbo& _vbo, const attribparams& _attribs)
	{
		vaoparam v{ _vbo, _attribs };
		return v;
	}
}