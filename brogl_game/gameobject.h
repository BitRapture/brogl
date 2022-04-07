#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

// Local dependencies
#include "../brogl/brogl.h"
#include "_scenemanager.h"
#include "_timemanager.h"
#include "_sysmanager.h"
#include "_inputmanager.h"
#include "_rendermanager.h"
#include "_objectmanager.h"
#include "managers.h"

// External dependencies
#include <GLM/glm.hpp>

// STL dependencies
#include <string>

namespace bro
{
	class transformation
	{
	public:
		glm::vec3 position{ 0, 0, 0 };
		glm::vec3 direction{ 1, 0, 0 };

	public:
	};

	class gameobject
	{
	protected:
		// Handle to engine's scene manager
		_scenemanager& Scenes;

		// Handle to engine's time manager
		_timemanager& Time;

		// Handle to engine's system manager
		_sysmanager& System;

		// Handle to engine's input manager
		_inputmanager& Input;

		// Handle to engine's render manager
		_rendermanager& Render;

		// Handle to engine's object and resource manager
		_objectmanager& Objects;

		std::string objectName{ "defaultObject" };

	public:
		transformation transform;

	public:
		virtual void OnAwake() {};
		virtual void OnStart() {};
		virtual void Update() {};
		virtual void OnDestroy() {};
		virtual void OnCollide(gameobject& _object) {};

	public:
		bool operator==(const gameobject& _object) const { return this->objectName == _object.objectName; }
		bool operator==(const gameobject* _object) const { return this->objectName == _object->objectName; }
		bool operator==(const char* _objectName) const { return this->objectName == _objectName; }

	public:

		gameobject(const char* _objectName, const managers& _managers)
			: objectName{ _objectName }, Scenes{ _managers.Scenes }, Time{ _managers.Time },
			System{ _managers.System }, Input{ _managers.Input }, Render{ _managers.Render },
			Objects{ _managers.Objects }
		{};

	};

}

#endif // !_GAMEOBJECT_H_
