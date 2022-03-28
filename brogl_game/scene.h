/// Scenes of a game
#ifndef _SCENE_H_
#define _SCENE_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"
#include "_inputmanager.h"

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

	protected:
		// Handle to engine's scene manager
		_scenemanager& Scenes;

		// Handle to engine's time manager
		_timemanager& Time;

		// Handle to engine's system manager
		_sysmanager& System;

		// Handle to engine's input manager
		_inputmanager& Input;

		// Scene name
		std::string sceneName{ "defaultScene" };

	protected: // Safe manager getters for scene derivation
		/// @brief Get the scene manager
		/// @return Scene manager
		//_scenemanager& Scenes() { if (sceneManager == nullptr) { throw std::runtime_error("Scene manager not initialized"); } return *sceneManager; }
		/// @brief Get the time manager
		/// @return Time manager
		//_timemanager& Time() { if (timeManager == nullptr) { throw std::runtime_error("Time manager not initialized"); } return *timeManager; }
		/// @brief Get the system manager
		/// @return System manager
		//_sysmanager& System() { if (systemManager == nullptr) { throw std::runtime_error("System manager not initialized"); } return *systemManager; }
		/// @brief Get the input manager
		/// @return Input manager
		//_inputmanager& Input() { if (inputManager == nullptr) { throw std::runtime_error("Input manager not initialized"); } return *inputManager; }

	private: // Engine related internal methods
		friend engine;

		/// @brief Allow the engine to update the scene
		void EngineUpdate();

		/// @brief Allow the engine to render the scene
		void EngineRender();

		/// @brief Allow the engine to connect to the scene on creation
		/// @param _scenes Reference to the scene manager
		//void EngineConnect(_scenemanager& _scenes, _timemanager& _time, _sysmanager& _system,
		//	_inputmanager& _input) 
		//{ 
		//	sceneManager = &_scenes; 
		//	timeManager = &_time;
		//	systemManager = &_system;
		//	inputManager = &_input;
		//};

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

	public: // Operator overloads
		// Compare scenes
		bool operator==(const scene& _scene) const { return this->sceneName == _scene.sceneName; }
		bool operator==(const scene* _scene) const { return this->sceneName == _scene->sceneName; }
		bool operator==(const char* _sceneName) const { return this->sceneName == _sceneName; }

	public: // Instantiation

		/// @brief Scene constructor
		/// @param _sceneName Name to be given to instantiated scene
		scene(const char* _sceneName, _scenemanager& _sceneManager, _timemanager& _timeManager,
			_sysmanager& _systemManager, _inputmanager& _inputManager
			) 
			: sceneName{ _sceneName }, Scenes{ _sceneManager }, Time{ _timeManager },
			System{ _systemManager }, Input{ _inputManager }
		{};
	};
}

#endif // !_SCENE_H_
