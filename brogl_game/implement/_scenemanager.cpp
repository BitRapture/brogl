#include "../_scenemanager.h"

namespace bro
{

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