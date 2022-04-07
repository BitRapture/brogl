/// All encompasing managers header
#ifndef _MANAGERS_H_
#define _MANAGERS_H_

namespace bro
{
	// Forward decls
	class _timemanager;
	class _sysmanager;
	class _scenemanager;
	class _rendermanager;
	class _inputmanager;
	class _objectmanager;

	struct managers
	{
	public:
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

	public:
		managers(_scenemanager& _sceneManager, _timemanager& _timeManager,
			_sysmanager& _systemManager, _inputmanager& _inputManager, _rendermanager& _renderManager,
			_objectmanager& _objectManager
		)
			: Scenes{ _sceneManager }, Time{ _timeManager }, System{ _systemManager }, 
			Input{ _inputManager }, Render{ _renderManager }, Objects{ _objectManager }
		{};
	};
}

#endif // !_MANAGERS_H_
