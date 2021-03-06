#include "../engine.h"

namespace bro
{

	void engine::Start()
	{
		// Start managers
		renderManager.EngineStart(systemManager.window);
		inputManager.EngineStart();
		sceneManager.EngineStart();
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

	engine::engine(const char* _title, int _windowWidth, int _windowHeight)
	{
		// Set system manager settings
		systemManager.title = _title;
		systemManager.windowWidth = _windowWidth;
		systemManager.windowHeight = _windowHeight;

		// Initialize SDL
		if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) { throw std::runtime_error("Failed to initialize SDL"); }

		// Initialize SDL opengl context 
		systemManager.window = bro::InitializeContext(systemManager.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, systemManager.windowWidth, systemManager.windowHeight);

	}

}