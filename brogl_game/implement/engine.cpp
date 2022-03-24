#include "../engine.h"

namespace bro
{

	void engine::Start()
	{

	}

	void engine::Exit()
	{

	}

	void engine::Run()
	{
		Start();

		// Main engine loop
		while (!systemManager.quitting)
		{
			inputManager.EnginePreUpdate();

			// SDL event polling
			SDL_Event ev;
			while (SDL_PollEvent(&ev))
			{
				switch (ev.type)
				{
					case SDL_QUIT:
						systemManager.Quit();
					break;
				}
			}

			// Update input manager
			inputManager.EnginePostUpdate();

			// Update time manager
			timeManager.deltaTime = 0;

			// Update the current scene
			sceneManager.GetCurrentScene()->EngineUpdate();
			sceneManager.GetCurrentScene()->EngineRender();
		}

		Exit();
	}

}