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
#pragma once

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Plasmogrify::Application::Application pPlasmogrify;
    pPlasmogrify.Init(hInstance, nCmdShow);
    return pPlasmogrify.MainLoop();
}


