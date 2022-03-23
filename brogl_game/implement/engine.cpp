#include "../engine.h"

namespace bro
{

	bool engine::Run(const double& _deltaTime)
	{
		// Update time manager
		timeManager.deltaTime = _deltaTime;

		// Update the current scene
		sceneManager.GetCurrentScene()->EngineUpdate();
		sceneManager.GetCurrentScene()->EngineRender();

		// Return system quit status
		return systemManager.quitting;
	}

}