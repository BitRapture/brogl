/// Brogl game engine class, entry point for a game
#ifndef _ENGINE_H_
#define _ENGINE_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"
#include "_inputmanager.h"
#include "scene.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>

// STL dependencies
#include <vector>
#include <string>

namespace bro
{
	class engine
	{
	protected: // Internal managers
		// Scene manager
		_scenemanager sceneManager;

		// Time manager
		_timemanager timeManager;

		// Input manager
		_inputmanager inputManager;

		// Engine system manager
		_sysmanager systemManager;

	private: // Internal members


	private: // Internal methods
		/// @brief Start and initialize game engine 
		void Start();

		/// @brief Exit and free game engine
		void Exit();

	public:
		/// @brief Run game engine
		void Run();

		void AddScene(scene& _scene);

		engine(const char* _title, int _windowWidth, int _windowHeight);
		engine() {};
	};
}

#endif // !_ENGINE_H_
