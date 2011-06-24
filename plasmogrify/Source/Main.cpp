///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Main.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plamogrify Framework Main
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Plasmogrify::Application* pPlasmogrify = new Plasmogrify::Application();
	pPlasmogrify->Init(hInstance, nCmdShow);
	return pPlasmogrify->MainLoop();
}


