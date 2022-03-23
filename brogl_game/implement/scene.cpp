#include "../scene.h"

namespace bro
{
	void scene::EngineUpdate()
	{
		// Physics update 

		// Update objects

		// Polymorphic late scene update
		SceneUpdate();
	}

	void scene::EngineRender()
	{
		// Render update


		// Polymorphic late scene render
		SceneRender();
	}
}