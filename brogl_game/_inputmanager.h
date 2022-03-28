/// Input manager for SDL event polling 
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

// External dependencies
#include <SDL2/SDL.h>
#include <GLM/glm.hpp>

// STL dependencies
#include <unordered_map>
#include <stdexcept>
#include <string>
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
		// Mouse state for buttons
		int mouseState{ 0 };
		// Mouse mask for changed buttons
		int mouseMask{ 0 };

		// Button axes allow for a range between -1 and 1
		struct axis
		{
			// Positive and negative key scancodes to check
			SDL_Scancode posKey, negKey;
		};
		// Axis list 
		std::vector<axis> buttonAxes;
		// Indices map to retreive index for specific axis
		std::unordered_map<std::string, size_t> axesIndices;

	private: // Internal engine methods
		friend engine;

		void EnginePreUpdate();

		void EnginePostUpdate();

	public:
		bool GetKey(const SDL_Scancode& _scanCode);

		bool GetKeyDown(const SDL_Scancode& _scanCode);

		bool GetKeyUp(const SDL_Scancode& _scanCode);

		bool GetMouseButton(const int& _button);

		bool GetMouseButtonDown(const int& _button);

		bool GetMouseButtonUp(const int& _button);

		glm::vec3 GetMousePosition() { return { mouseX, mouseY, 0 }; };

		size_t GetAxisIndex(const char* _axisName);

		float GetAxis(const char* _axisName);
		float GetAxis(const size_t& _axisIndex);

		void AddAxis(const char* _axisName, const SDL_Scancode& _positiveKey, const SDL_Scancode& _negativeKey);

	public:
		_inputmanager();
		~_inputmanager();

	};

}

#endif // !_INPUTMANAGER_H_
