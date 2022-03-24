#include "../_scenemanager.h"
#include "../scene.h"

namespace bro
{
	void _scenemanager::AddScene(scene& _scene) 
	{ 
		sceneMap[_scene.GetName()] = &_scene; 
	}

	void _scenemanager::UnloadScene()
	{
		scene* current = currentScene->second;
		current->SceneOnUnload();
	}

	void _scenemanager::LoadScene()
	{
		scene* current = currentScene->second;
		current->SceneOnLoad();
	}

}