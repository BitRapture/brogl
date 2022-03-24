/// Engine scene manager
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

// STL dependencies
#include <stdexcept>
#include <map>

namespace bro
{
	class scene;
	class engine;

	class _scenemanager
	{
	private:
		// Map of handles to scenes
		std::map<std::string, scene*> sceneMap;
		// Current scene loaded
		std::map<std::string, scene*>::iterator currentScene;

	private: // Internal methods
		/// @brief Internal scene loading method
		void LoadScene();
		
		/// @brief Internal scene unloading method
		void UnloadScene();

	private: // Engine related internal methods
		friend engine;

		/// @brief Add a scene to the manager
		/// @param _scene Reference to scene
		void AddScene(scene& _scene);

		/// @brief 
		/// @param _name 
		scene* GetCurrentScene() { return currentScene->second; }

	public:
		/// @brief 
		void NextScene() 
		{ 
			UnloadScene();
			currentScene++;
			LoadScene();
		}

		/// @brief 
		void PreviousScene()
		{
			UnloadScene();
			currentScene--;
			LoadScene();
		}

		/// @brief 
		/// @param _name 
		void GotoScene(std::string _name)
		{
			UnloadScene();
			currentScene = sceneMap.find(_name);
			LoadScene();
		}

	};
}

#endif // !_SCENEMANAGER_H_
