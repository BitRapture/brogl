/// Game object and resource runtime manager
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

// Local dependencies
#include "../brogl/brogl.h"

// STL dependencies
#include <vector>
#include <unordered_map>
#include <string>

namespace bro
{
	class gameobject;
	class component;

	class _objectmanager
	{
	private:
		// Map of global resources
		std::unordered_map<std::string, glhandle*> resources;

	public:
		void AddResource(const char* _name, glhandle& _resource) { resources[_name] = &_resource; }
		glhandle* GetResource(const char* _name) { return resources[_name]; }

	};

}

#endif // !_OBJECTMANAGER_H_
