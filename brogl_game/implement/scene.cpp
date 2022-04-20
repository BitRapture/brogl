#include "../scene.h"

namespace bro
{
	void scene::EngineUpdate()
	{
		// Physics update 

		// Update objects
		for (gameobject* object : gameObjects)
		{
			object->Update();
		}

		// Delete objects
		//for (std::list<gameobject*>::iterator it; it != gameObjects.end(); ++it)
		//{
		//	gameobject* go = *it;
		//	if (go->destroyed)
		//	{
		//		go->OnDestroy();
		//		it = gameObjects.erase(it);
		//	}
		//}

		// Polymorphic late scene update
		SceneUpdate();
	}

	void scene::EngineRender()
	{
		Render.Clear();

		// Render update
		for (gameobject* object : gameObjects)
		{
			for (rendercomponent* render : object->renderComponents)
			{
				render->Update();
			}
		}

		// Polymorphic late scene render
		SceneRender();

		// Display contents
		Render.EngineDisplay();
	}

	void scene::EngineOnLoad()
	{
		// Load objects
		for (gameobject* object : gameObjects)
		{
			object->OnStart();
		}

		// Polymorphic late scene on load
		SceneOnLoad();
	}

}