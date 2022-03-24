/// Scenes of a game
#ifndef _SCENE_H_
#define _SCENE_H_

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
#include <string>

namespace bro
{
	class _scenemanager;
	class engine;

	class scene
	{
	private:
		// Object pooling
		// gameobject => *

		// Object refs with physics components
		// gameobject -> component => physics => *

		// Object refs with render components
		// gameobject -> component => render => *

		// Object refs with camera components
		// gameObject -> component => camera => *

		// Handle to engine's scene manager
		_scenemanager* sceneManager{ nullptr };

		// Handle to engine's time manager
		_timemanager* timeManager{ nullptr };

		// Handle to engine's system manager
		_sysmanager* systemManager{ nullptr };

		// Handle to engine's input manager

		// Scene name
		std::string sceneName{ "defaultScene" };

	private: // Engine related internal methods
		friend engine;

		/// @brief Allow the engine to update the scene
		void EngineUpdate();

		/// @brief Allow the engine to render the scene
		void EngineRender();

		/// @brief Allow the engine to connect to the scene on creation
		/// @param _scenes Reference to the scene manager
		void EngineConnect(_scenemanager& _scenes, _timemanager& _time, _sysmanager& _system) 
		{ 
			sceneManager = &_scenes; 
			timeManager = &_time;
			systemManager = &_system;
		};

	public: // Scene related methods
		// gameobject& CreateObject()

	public: // Virtual methods
		/// @brief Called when the scene is loaded
		virtual void SceneOnLoad() { };

		/// @brief Called when the scene is unloaded
		virtual void SceneOnUnload() { };

		/// @brief Called late when the scene is updated
		/// @param _deltaTime Delta time (todo: create Time struct)
		virtual void SceneUpdate() { };

		/// @brief Called late when the scene is rendered
		virtual void SceneRender() { };

	public: // Getters
		/// @brief Get the name of the scene object
		/// @return Scene name
		std::string GetName() { return sceneName; }

	public: // Instantiation

		/// @brief Scene constructor
		/// @param _sceneName Name to be given to instantiated scene
		scene(std::string _sceneName) : sceneName{ _sceneName } {};
	};
}

#endif // !_SCENE_H_
