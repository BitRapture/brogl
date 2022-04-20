#include "../gameobject.h"
#include "../scene.h"

namespace bro
{

	void gameobject::LinkObject(gameobject* _object)
	{
		tiedScene->AddGameObject(_object);
		_object->OnCreate();
	}

	void gameobject::Destroy()
	{
		destroyed = true;
	}

}