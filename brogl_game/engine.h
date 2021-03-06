/// Brogl game engine class, entry point for a game
#ifndef _ENGINE_H_
#define _ENGINE_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"
#include "_inputmanager.h"
#include "_rendermanager.h"
#include "_objectmanager.h"
#include "scene.h"

// External dependencies
#include <SDL2/SDL.h>
#include <GLEW/glew.h>

// STL dependencies
#include <vector>
#include <string>
#include <type_traits>

namespace bro
{
	class engine
	{
	protected: // Internal managers
		// Scene manager
		_scenemanager sceneManager;

		// Time manager
		_timemanager timeManager;

		// Engine system manager
		_sysmanager systemManager;

		// Input manager
		_inputmanager inputManager;

		// Rendering manager
		_rendermanager renderManager;

		// Handle to engine's object and resource manager
		_objectmanager objectManager;

	private: // Internal members


	private: // Internal methods
		/// @brief Start and initialize game engine 
		void Start();

		/// @brief Exit and free game engine
		void Exit();

	public:
		/// @brief Run game engine
		void Run();

		/// @brief Create a new scene and add to scene manager
		/// @tparam s Scene class or derivation of scene class
		/// @param _sceneName Name for the scene
		/// @return Pointer to the dynamically created scene, will need to be freed
		template <class s>
		s* CreateScene(const char* _sceneName)
		{
			// Compile time check to make sure object is deriving from scene class
			static_assert(std::is_base_of<scene, s>::value, "Class does not derive from base scene");
			s* newScene = new s({ sceneManager, timeManager, systemManager, inputManager, renderManager, objectManager });
			sceneManager.AddScene(*newScene);
			return newScene;
		}

		/// @brief Create a default scene object
		/// @param _sceneName Name for the scene
		/// @return Pointer to the dynamically created scene, will need to be freed
		scene* CreateScene(const char* _sceneName)
		{
			return CreateScene<scene>(_sceneName);
		}

		/// @brief Add scene to scene manager manually
		/// @param _scene Scene to add
		void AddScene(scene* _scene)
		{
			sceneManager.AddScene(*_scene);
		}

		engine(const char* _title, int _windowWidth, int _windowHeight);
	};
}

#endif // !_ENGINE_H_
