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

namespace bro
{
	class engine
	{
	private: // Internal managers
		// Scene manager
		_scenemanager sceneManager;

		// Time manager
		_timemanager timeManager;

		// Engine system manager
		_sysmanager systemManager;

		// Input manager
		_inputmanager inputManager;

	private: // Internal methods
		/// @brief Start and initialize game engine 
		void Start();

		/// @brief Exit and free game engine
		void Exit();

	public:
		/// @brief Run game engine
		void Run();

		void AddScene(scene& _scene) 
		{ 
			_scene.EngineConnect(sceneManager, timeManager, systemManager); 
			sceneManager.AddScene(_scene); 
		}

	};
}

#endif // !_ENGINE_H_
