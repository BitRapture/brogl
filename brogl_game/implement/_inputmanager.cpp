#include "../_inputmanager.h"

namespace bro
{

	void _inputmanager::PollKeyInput()
	{
		// Copy over states from previous frame
		for (int i = 0; i < keyStateSize; ++i) { keyMask[i] = keyStates[i]; }

	}

	void _inputmanager::PollMouseInput()
	{
		mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	}

	void _inputmanager::EngineUpdate()
	{
		PollKeyInput();
		PollMouseInput();
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

	float _inputmanager::GetAxis(const char* _axisName)
	{

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