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

	bool _inputmanager::GetKey(const SDL_Scancode& _scanCode)
	{
		return keyStates[_scanCode];
	}

	bool _inputmanager::GetKeyDown(const SDL_Scancode& _scanCode)
	{
		return keyStates[_scanCode] && !keyMask[_scanCode];
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

	float _inputmanager::GetAxis(const char* _axisName)
	{
		return GetAxis(GetAxisIndex(_axisName));
	}
	float _inputmanager::GetAxis(const size_t& _axisIndex)
	{
		const axis& ax = buttonAxes[_axisIndex];
		// Test scancode buttons
		float d = GetKey(ax.posKey) - GetKey(ax.negKey);
		return d;
	}

	void _inputmanager::AddAxis(const char* _axisName, const SDL_Scancode& _positiveKey, const SDL_Scancode& _negativeKey)
	{
		buttonAxes.push_back({_positiveKey, _negativeKey});
		axesIndices[_axisName] = buttonAxes.size() - 1;
	}

	_inputmanager::_inputmanager()
	{
		// Connect to SDL
		keyStates = SDL_GetKeyboardState(&keyStateSize);
		keyMask = new unsigned char[keyStateSize];
	}

	_inputmanager::~_inputmanager()
	{
		delete[] keyMask;
	}

}