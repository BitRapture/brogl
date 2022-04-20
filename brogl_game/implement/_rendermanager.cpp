#include "../_rendermanager.h"

namespace bro
{

	void _rendermanager::EngineStart(SDL_Window* _window)
	{
		// Get window
		window = _window;

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		// Enable back face culling
		glEnable(GL_CULL_FACE);

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void _rendermanager::EngineDisplay()
	{
		SDL_GL_SwapWindow(window);
	}


	vao* _rendermanager::CreateVAO(const char* _name, const vaoparams& _params, const size_t& _vertexCount)
	{
		vao* newVAO = new vao{ bro::CreateVAO(_params) };
		vaos[_name] = { newVAO, _vertexCount };
		return newVAO;
	}

	void _rendermanager::Clear()
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


}