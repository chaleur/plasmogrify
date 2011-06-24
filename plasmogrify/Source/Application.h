///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Application.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasma Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Config.h"
#include <windows.h>

namespace Plasmogrify
{
	namespace System
	{
		namespace Graphics
		{
			class Device;
		}
	}
	class Application
	{
		public:
			Application();
			~Application();

			void Init(HINSTANCE hInstance, int nCmdShow);
			uint16_t MainLoop();

	    private:
			void InitWindow(HINSTANCE hInstance, int nCmdShow);
			void InitDevice();

		private:

			bool					      mbInit;
			HWND						  mHWND;
			System::Graphics::Device*     mpDevice;
	};
}