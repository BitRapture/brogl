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
#include "component.h"

// External dependencies
#include <GLM/glm.hpp>

// STL dependencies
#include <string>
#include <vector>
#include <type_traits>

namespace bro
{
	class scene;

	class transformation
	{
	public:
		glm::vec3 position{ 0, 0, 0 };
		glm::vec3 direction{ 1, 0, 0 };

	public:
	};

	class gameobject
	{
	private: // Internal members
		friend scene;

		// Array of all render components of an instance
		std::vector<rendercomponent*> renderComponents;

		// Array of all physics components of an instance
		std::vector<physicscomponent*> physicsComponents;
		
		// Array of all collision components of an instance
		std::vector<collisioncomponent*> collisionComponents;

		// Scene this instance is tied to
		scene* tiedScene{ nullptr };

		// Destruction flag
		bool destroyed{ false };

	protected: // Global systems
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

		// Name of this specific instance
		std::string objectName{ "defaultObject" };

	public: // Public members
		// Gameobject transform
		transformation transform;

	private: // Internal methods
		/// @brief Link a new object to the scene 
		/// @param _object New object to link
		void LinkObject(gameobject* _object);

	protected: // Protected methods
		/// @brief Instantiate a new gameobject
		/// @tparam g Gameobject class or derivation of gameobject class
		/// @return Pointer to dynamically created gameobject, will need to be freed
		template <class g>
		g* Instantiate()
		{
			static_assert(std::is_base_of<gameobject, g>::value, "Class does not derive from base gameobject");
			g* go = new g({ Scenes, Time, System, Input, Render, Objects });
			LinkObject(go);
			return go;
		}
		
		/// @brief Add render component to instance
		/// @param _renderComponent Render component to add
		void AddRenderComponent(rendercomponent* _renderComponent)
		{
			renderComponents.push_back(_renderComponent);
		}
		
		/// @brief Add physics component to instance
		/// @param _physicsComponent Physics component to add
		void AddPhysicsComponent(physicscomponent* _physicsComponent)
		{
			physicsComponents.push_back(_physicsComponent);
		}

		/// @brief Add collision component to instance
		/// @param _colComponent Collision component to add
		void AddCollisionComponent(collisioncomponent* _colComponent)
		{
			collisionComponents.push_back(_colComponent);
		}

	public: // Public methods
		/// @brief Mark instance to be destroyed
		void Destroy();

	public: // Virtual methods

		virtual void OnCreate() {};

		virtual void OnStart() {};

		virtual void Update() {};

		virtual void OnDestroy() {};

		virtual void OnCollide(gameobject& _object) {};


	public:

		/// @brief Gameobject construction
		/// @param _managers Handle to all managers
		gameobject(const managers& _managers)
			: Scenes{ _managers.Scenes }, Time{ _managers.Time },
			System{ _managers.System }, Input{ _managers.Input }, Render{ _managers.Render },
			Objects{ _managers.Objects }
		{};

	};

}

#endif // !_GAMEOBJECT_H_
