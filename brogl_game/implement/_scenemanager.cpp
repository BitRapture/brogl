#include "../_scenemanager.h"
#include "../scene.h"

namespace bro
{
	void _scenemanager::AddScene(scene& _scene) 
	{ 
		scenes.push_back(&_scene); 
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
		currentScene = scenes.begin() + _index;
		LoadScene();
	}
	void _scenemanager::GotoScene(const char* _sceneName)
	{
		UnloadScene();
		currentScene = std::find_if(scenes.begin(), scenes.end(), [&_sceneName](scene* _scene) { return *_scene == _sceneName; });
		LoadScene();
	}

	void _scenemanager::SetSceneIndices(std::vector<size_t> _indices)
	{
		sceneIndices = _indices;
	}
	void _scenemanager::SetSceneIndices(std::vector<const char*> _sceneNames)
	{
		sceneIndices.clear();
		for (const char* name : _sceneNames)
		{
			sceneIndices.push_back(std::distance(scenes.begin(), std::find(scenes.begin(), scenes.end(), name)));
		}
	}

	void _scenemanager::AddSceneIndex(size_t _index)
	{
		sceneIndices.push_back(_index);
	}
	void _scenemanager::AddSceneIndex(const char* _sceneName)
	{
		sceneIndices.push_back(std::distance(scenes.begin(), std::find(scenes.begin(), scenes.end(), _sceneName)));
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

	void _scenemanager::ResetSceneIndex()
	{
		currentIndex = sceneIndices.begin();
	}

	_scenemanager::_scenemanager()
	{
		currentScene = scenes.begin();
		currentIndex = sceneIndices.begin();
	}

}