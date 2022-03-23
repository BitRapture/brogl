/// Brogl game engine class, entry point for a game
#ifndef _ENGINE_H_
#define _ENGINE_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>

// STL dependencies
#include <vector>

namespace bro
{
	class engine
	{
	private:
		// Scene manager
		_scenemanager sceneManager;

		// Time manager
		_timemanager timeManager;

		// Engine system manager
		_sysmanager systemManager;

	public:
		/// @brief Run game engine
		/// @param _deltaTime Delta time of a frame (todo: remove param, insert in body)
		/// @return Quit status of program (todo: make void, return from loop in body)
		bool Run(const double& _deltaTime);

		void AddScene(scene& _scene) 
		{ 
			_scene.EngineConnect(sceneManager, timeManager); 
			sceneManager.AddScene(_scene); 
		}

	};
}

#endif // !_ENGINE_H_
