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

		/// @brief Get current scene handle
		/// @return Handle to current scene
		scene* GetCurrentScene() { return *currentScene; }

		/// @brief Initialize manager on engine start up
		void EngineStart();

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

		/// @brief Set scene indices
		/// @param _indices New indices to set 
		void SetSceneIndices(std::vector<size_t> _indices);
		/// @brief Set scene indices
		/// @param _sceneNames Scene names to get indices from
		void SetSceneIndices(std::vector<const char*> _sceneNames);

		/// @brief Push scene index to indices list
		/// @param _index Index of scene
		void AddSceneIndex(size_t _index);
		/// @brief Push scene index to indices list
		/// @param _sceneName Scene name to get index from
		void AddSceneIndex(const char* _sceneName);

		/// @brief Find the index of a scene from the scene manager
		/// @param _sceneName Name of the scene
		/// @return Index of scene
		size_t FindSceneIndex(const char* _sceneName);

		/// @brief Go to next scene handle from indices list
		void NextScene();
		/// @brief Go to previous scene handle from indices list
		void PreviousScene();

		/// @brief Reset to the beginning of the indices list, doesn't change the current scene
		void ResetSceneIndices();

	};
}

#endif // !_SCENEMANAGER_H_
