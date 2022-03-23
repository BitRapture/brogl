/// System manager for game engine
#ifndef _SYSMANAGER_H_
#define _SYSMANAGER_H_

namespace bro
{
	class engine;

	class _sysmanager
	{
	private: // Internal engine members
		friend engine;
		// Quitting flag raised when engine quits
		bool quitting{ false };

	public:
		void Quit() { quitting = true; };

	};

}

#endif // !_SYSMANAGER_H_
