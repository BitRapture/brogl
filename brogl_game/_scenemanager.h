/// Engine scene manager
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

// STL dependencies
#include <stdexcept>
#include <algorithm>
#include <vector>

namespace bro
{
	class scene;
	class engine;

	class _scenemanager
	{
	private:
		// Vector of handles to scenes
		std::vector<scene*> scenes;
		// Current scene loaded
		std::vector<scene*>::iterator currentScene;

		// Scene indices for scene traversal
		std::vector<size_t> sceneIndices;
		// Current scene index
		std::vector<size_t>::iterator currentIndex;

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
		scene* GetCurrentScene() { return *currentScene; }

	public:
		/// @brief Go to next immediate scene handle
		void NextImmediateScene();

		/// @brief Go to previous immediate scene handle
		void PreviousImmediateScene();

		/// @brief Go to specific scene
		/// @param _index Index of the scene
		void GotoScene(int _index);
		/// @brief Go to specific scene
		/// @param _sceneName Name of the scene
		void GotoScene(const char* _sceneName);

		void SetSceneIndices(std::vector<size_t> _indices);
		void SetSceneIndices(std::vector<const char*> _sceneNames);

		void AddSceneIndex(size_t _index);
		void AddSceneIndex(const char* _sceneName);

		void NextScene();
		void PreviousScene();

		void ResetSceneIndex();

	public:
		_scenemanager();
	};
}

#endif // !_SCENEMANAGER_H_
