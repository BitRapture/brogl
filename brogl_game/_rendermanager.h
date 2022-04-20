/// Rendering component for graphical output of engine
#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

// Local dependencies
#include "../brogl/brogl.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

// STL dependencies
#include <unordered_map>
#include <string> 

namespace bro
{
	class engine;
	class scene;

	class _rendermanager
	{
	private: // Internal members
		/// Pointer to the window from system
		SDL_Window* window{ nullptr };

		// Map of global VAOs
		struct mVAOS { vao* v{ nullptr }; size_t verts{ 0 }; };
		std::unordered_map<std::string, mVAOS> vaos;

		// Map of global shaders
		std::unordered_map<std::string, shaderprogram*> shaders;

		// Clear color
		glm::vec4 clearColor{ 0, 0, 0, 1 };

	private: // Engine related methods
		friend engine;

		void EngineStart(SDL_Window* _window);

	private: // Scene related methods
		friend scene;

		void EngineDisplay();

	public: // Public methods

		/// @brief Add VAO to render manager
		/// @param _name Name of the VAO
		/// @param _vao Handle to the VAO
		void AddVAO(const char* _name, vao& _vao, const size_t& _vertexCount) { vaos[_name] = { &_vao, _vertexCount }; }

		/// @brief Get VAO from render manager
		/// @param _name Name of the VAO
		/// @return Pointer to the VAO
		vao* GetVAO(const char* _name) { return vaos[_name].v; }

		/// @brief Get total vertices for a VAO
		/// @param _name Name of the VAO
		/// @return Vertex count
		size_t GetVAOvertices(const char* _name) { return vaos[_name].verts; }

		/// @brief Dynamically create and add a new VAO
		/// @param _name Name of the VAO
		/// @param _params VAO parameters
		/// @return Pointer to the dynamically create VAO, will need to be freed
		vao* CreateVAO(const char* _name, const vaoparams& _params, const size_t& _vertexCount);

		void AddShader(const char* _name, shaderprogram& _shader) { shaders[_name] = &_shader; }
		shaderprogram* GetShader(const char* _name) { return shaders[_name]; }

		/// @brief Clear the screen
		void Clear();

		/// @brief Set the clear color
		/// @param _rgba RGBA format
		void SetClearColor(const glm::vec4& _rgba) { clearColor = _rgba; }

	};

}

#endif // !_RENDERMANAGER_H_
