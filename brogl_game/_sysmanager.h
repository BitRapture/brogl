/// System manager for game engine
#ifndef _SYSMANAGER_H_
#define _SYSMANAGER_H_

// External dependencies
#include <SDL2/SDL.h>

// STL dependencies
#include <string>

namespace bro
{
	class engine;

	class _sysmanager
	{
	private: // Internal engine members
		friend engine;
		// Quitting flag raised when engine quits
		bool quitting{ false };
		
		// Window title
		std::string title{ "Untitled Project" };

		// Window dimensions
		int windowWidth{ 1280 }, windowHeight{ 720 };

		// Handle to the main SDL window
		SDL_Window* window{ nullptr };

	public:
		/// @brief Quit game engine runtime
		void Quit() { quitting = true; };

		/// @brief Check if game engine is quitting execution
		/// @return Quitting flag
		const bool& IsQuitting() { return quitting; }

		/// @brief Set the window title
		/// @param _title Title text
		void SetTitle(const char* _title) { title = _title; SDL_SetWindowTitle(window, title.c_str()); }

		/// @brief Get the current window title
		/// @return Title text
		std::string GetTitle() { return title; }
	};

}

#endif // !_SYSMANAGER_H_
