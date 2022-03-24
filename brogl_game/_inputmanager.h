/// Input manager for SDL event polling 
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

// External dependencies
#include <SDL2/SDL.h>

// STL dependencies
#include <unordered_map>
#include <vector>

namespace bro
{

	class engine;

	class _inputmanager
	{
	private:
		// SDL handle to key states
		const unsigned char* keyStates{ nullptr };
		int keyStateSize{ 0 };

		// Key state mask for changed keys
		unsigned char* keyMask{ nullptr };

		// Mouse coordinates
		int mouseX{ 0 }, mouseY{ 0 };
		// Mouse state
		int mouseState{ 0 };

	private: // Internal manager methods
		void PollKeyInput();

		void PollMouseInput();

	private: // Internal engine methods
		friend engine;

		void EngineUpdate();

	public:
		bool GetKey(const SDL_Scancode& _scanCode);

		bool GetKeyDown(const SDL_Scancode& _scanCode);

		bool GetKeyUp(const SDL_Scancode& _scanCode);



		float GetAxis(const char* _axisName);

	public:
		_inputmanager();
		~_inputmanager();

	};

}

#endif // !_INPUTMANAGER_H_
