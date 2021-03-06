#ifndef _TOOLS_H_
#define _TOOLS_H_

// Local dependencies
#include "defs.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>

// STL dependencies
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

namespace bro
{
	/// @brief Read contents of a text file
	/// @param _filepath Filepath to the file
	/// @return Extracted information as a string
	std::string ReadFile(const char* _filepath);

	struct wfobj
	{
		vbo vertices;
		vbo texcoords;
		vbo normals;

		size_t verticesCount{ 0 };
	};

	/// @brief Open a wavefront object file
	/// @param _filepath Filepath to the file
	/// @return Wavefront object
	wfobj OpenWFObj(const char* _filepath);

}


#endif // !_TOOLS_H_
