#include "../_scenemanager.h"
#include "../scene.h"

namespace bro
{
	void _scenemanager::AddScene(scene& _scene) 
	{ 
		scenes.push_back(&_scene); 
	}

	void _scenemanager::EngineStart()
	{
		// Connect iterators to containers
		currentScene = scenes.begin();
		currentIndex = sceneIndices.begin();

		// Load first scene
		LoadScene();
	}

	void _scenemanager::LoadScene()
	{
		scene* current = *currentScene;
		current->SceneOnLoad();
	}

	void _scenemanager::UnloadScene()
	{
		scene* current = *currentScene;
		current->SceneOnUnload();
	}

	void _scenemanager::NextImmediateScene()
	{
		UnloadScene();
		currentScene++;
		LoadScene();
	}

	void _scenemanager::PreviousImmediateScene()
	{
		UnloadScene();
		currentScene--;
		LoadScene();
	}

	void _scenemanager::GotoScene(int _index)
	{
		UnloadScene();
		if (scenes.begin() + _index >= scenes.end()) { throw std::runtime_error("Scene index out of bounds"); }
		currentScene = scenes.begin() + _index;
		LoadScene();
	}
	void _scenemanager::GotoScene(const char* _sceneName)
	{
		UnloadScene();
		currentScene = scenes.begin() + FindSceneIndex(_sceneName);
		LoadScene();
	}

	void _scenemanager::SetSceneIndices(std::vector<size_t> _indices)
	{
		sceneIndices = _indices;
	}
	void _scenemanager::SetSceneIndices(std::vector<const char*> _sceneNames)
	{
		sceneIndices.clear();
		// Iterate through scene names
		for (const char* name : _sceneNames)
		{
			sceneIndices.push_back(FindSceneIndex(name));
		}
	}

	void _scenemanager::AddSceneIndex(size_t _index)
	{
		sceneIndices.push_back(_index);
	}
	void _scenemanager::AddSceneIndex(const char* _sceneName)
	{
		sceneIndices.push_back(FindSceneIndex(_sceneName));
	}

	size_t _scenemanager::FindSceneIndex(const char* _sceneName)
	{
		// Find index of scene that matches sceneName within the scene manager
		ptrdiff_t index = std::distance(scenes.begin(), std::find_if(scenes.begin(), scenes.end(), [&_sceneName](scene* _scene) { return *_scene == _sceneName; }));
		if (index < 0) { throw std::runtime_error("Scene does not exist within scene manager"); }
		return index;
	}

	void _scenemanager::NextScene()
	{
		UnloadScene();
		currentScene = scenes.begin() + *currentIndex;
		currentIndex++;
		LoadScene();
	}
	void _scenemanager::PreviousScene()
	{
		UnloadScene();
		currentScene = scenes.begin() + *currentIndex;
		currentIndex--;
		LoadScene();
	}

	void _scenemanager::ResetSceneIndices()
	{
		currentIndex = sceneIndices.begin();
	}

}