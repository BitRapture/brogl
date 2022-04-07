/// Scenes of a game
#ifndef _SCENE_H_
#define _SCENE_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"
#include "_inputmanager.h"
#include "_rendermanager.h"
#include "managers.h"

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

		// Handle to engine's render manager
		_rendermanager& Render;

		// Handle to engine's object and resource manager
		_objectmanager& Objects;

		// Scene name
		std::string sceneName{ "defaultScene" };

	private: // Engine related internal methods
		friend engine;

		/// @brief Allow the engine to update the scene
		void EngineUpdate();

		/// @brief Allow the engine to render the scene
		void EngineRender();

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
		scene(const char* _sceneName, const managers& _managers)
			: sceneName{ _sceneName }, Scenes{ _managers.Scenes }, Time{ _managers.Time },
			System{ _managers.System }, Input{ _managers.Input }, Render{ _managers.Render },
			Objects{ _managers.Objects }
		{};
		// Todo replace this garbage with a managers struct 
	};
}

#endif // !_SCENE_H_
