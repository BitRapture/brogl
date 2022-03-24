/// System manager for game engine
#ifndef _SYSMANAGER_H_
#define _SYSMANAGER_H_

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

	public:
		/// @brief Quit game engine runtime
		void Quit() { quitting = true; };

		/// @brief Check if game engine is quitting execution
		/// @return Quitting flag
		const bool& IsQuitting() { return quitting; }

		void SetTitle(const char* _title) { title = _title; }

		std::string GetTitle() { return title; }
	};

}

#endif // !_SYSMANAGER_H_
