#include "../_inputmanager.h"

namespace bro
{

	void _inputmanager::EnginePreUpdate()
	{
		// Copy over key states from previous frame
		for (int i = 0; i < keyStateSize; ++i) { keyMask[i] = keyStates[i]; }
		// Copy over mouse states from previous frame
		mouseMask = mouseState;
	}

	void _inputmanager::EnginePostUpdate()
	{
		// Capture mouse state and position
		mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	}

	void _inputmanager::EngineStart()
	{
		// Fetch controllers at beginning of program
		FetchControllers();
	}

	void _inputmanager::CloseControllers()
	{
		for (SDL_GameController* controller : controllers)
		{
			SDL_GameControllerClose(controller);
		}
		controllers.clear();
	}

	bool _inputmanager::GetKey(const SDL_Keycode& _keyCode)
	{
		return GetKey(SDL_GetScancodeFromKey(_keyCode));
	}
	bool _inputmanager::GetKey(const SDL_Scancode& _scanCode)
	{
		return keyStates[_scanCode];
	}

	bool _inputmanager::GetKeyDown(const SDL_Keycode& _keyCode)
	{
		return GetKeyDown(SDL_GetScancodeFromKey(_keyCode));
	}
	bool _inputmanager::GetKeyDown(const SDL_Scancode& _scanCode)
	{
		return keyStates[_scanCode] && !keyMask[_scanCode];
	}

	bool _inputmanager::GetKeyUp(const SDL_Keycode& _keyCode)
	{
		return GetKeyUp(SDL_GetScancodeFromKey(_keyCode));
	}
	bool _inputmanager::GetKeyUp(const SDL_Scancode& _scanCode)
	{
		return !keyStates[_scanCode] && keyMask[_scanCode];
	}

	bool _inputmanager::GetMouseButton(const int& _button)
	{
		return (mouseState & SDL_BUTTON(_button)) != 0;
	}

	bool _inputmanager::GetMouseButtonDown(const int& _button)
	{
		return (mouseState & SDL_BUTTON(_button)) != 0 && (mouseMask & SDL_BUTTON(_button)) == 0;
	}

	bool _inputmanager::GetMouseButtonUp(const int& _button)
	{
		return (mouseState & SDL_BUTTON(_button)) == 0 && (mouseMask & SDL_BUTTON(_button)) != 0;
	}

	size_t _inputmanager::GetAxisIndex(const char* _axisName)
	{
		std::unordered_map<std::string, size_t>::iterator it = axesIndices.find(_axisName);
		if (it == axesIndices.end()) { throw std::runtime_error("Could not find axis name"); }
		return it->second;
	}

	float _inputmanager::GetAxis(const char* _axisName, const size_t& _controller)
	{
		return GetAxis(GetAxisIndex(_axisName), _controller);
	}
	float _inputmanager::GetAxis(const size_t& _axisIndex, const size_t& _controller)
	{
		const axis& ax = buttonAxes[_axisIndex];
		bool conConnect = controllers.size() > 0;
		// Test scancode buttons
		float d = (ax.enableKeys ? GetKey(ax.posKey) - GetKey(ax.negKey) : 0);
		// Test game controller axis
		if (d == 0 && ax.enableAxis && conConnect)
		{
			float controllerAxis = SDL_GameControllerGetAxis(controllers[_controller], ax.controllerAxis);
			d = controllerAxis / (controllerAxis >= 0 ? 32767 : 32768);
			d = ((controllerAxis >= 0 ? 1 : -1) * d > controllerDeadZone ? d : 0);
		}
		// Test game controller buttons
		d = (d == 0 && ax.enableButtons && conConnect ?
			SDL_GameControllerGetButton(controllers[_controller], ax.posButton) - 
			SDL_GameControllerGetButton(controllers[_controller], ax.negButton) : d);
		return d;
	}

	void _inputmanager::AddAxis(const char* _axisName, const SDL_Scancode& _posKey, const SDL_Scancode& _negKey)
	{
		axis ax;
		ax.posKey = _posKey;
		ax.negKey = _negKey;
		ax.enableKeys = true;
		AddAxis(_axisName, ax);
	}
	void _inputmanager::AddAxis(const char* _axisName, const axis& _axisParams)
	{
		buttonAxes.push_back(_axisParams);
		axesIndices[_axisName] = buttonAxes.size() - 1;
	}

	size_t _inputmanager::FetchControllers()
	{
		CloseControllers();
		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			if (SDL_IsGameController(i))
			{
				SDL_GameController* controller = SDL_GameControllerOpen(i);
				if (controller != nullptr) { controllers.push_back(controller); }
			}
		}
		return controllers.size();
	}

	_inputmanager::_inputmanager()
	{
		// Connect to SDL
		keyStates = SDL_GetKeyboardState(&keyStateSize);
		keyMask = new unsigned char[keyStateSize];
	}

	_inputmanager::~_inputmanager()
	{
		// Delete dynamic memory
		delete[] keyMask;

		// Close controllers
		CloseControllers();
	}

}