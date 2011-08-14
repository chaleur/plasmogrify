///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Application.cpp
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Application
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "System/Graphics/Device.h"
#include "World/WorldData.h"
#include "Timer.h"

#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_ACTIVATE:
        {
            uint32_t i = 0;
            uint32_t k = 2;
            i += k;
            break;
        }
        case WM_SIZE:
        {
            uint32_t i = 0;
            uint32_t k = 2;
            i += k;
            break;
        }
        case WM_ENTERSIZEMOVE:
        {
            uint32_t i = 0;
            uint32_t k = 2;
            i += k;
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

namespace Plasmogrify
{
    namespace Application
    {
        Application::Application()
            : mbInit(false)
            , mHWND(NULL)
            , mpDevice(NULL)
            , mpWorldData(NULL)
        {

        }

        Application::~Application()
        {
            if (mpDevice)
            {
                delete mpDevice;
            }

            if (mpWorldData)
            {
                delete mpWorldData;
            }
        }

        void Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
        {
            WNDCLASSEX wc;

            ZeroMemory(&wc, sizeof(WNDCLASSEX));

            wc.cbSize = sizeof(WNDCLASSEX);
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = hInstance;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            //wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wc.lpszClassName = "WindowClass1";

            RegisterClassEx(&wc);

            RECT wr = {0, 0, 800, 600}; 
            AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

            mHWND = CreateWindowEx(NULL, "WindowClass1", "Plasmogrify", WS_OVERLAPPEDWINDOW, 300, 300, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

            ShowWindow(mHWND, nCmdShow);
        }

        void Application::InitDevice()
        {
            mpDevice = new System::Graphics::Device();
            mpDevice->Init(mHWND);
        }

        void Application::InitWorld()
        {
            mpWorldData = new World::WorldData();
            mpWorldData->Init(mpDevice);
        }

        void Application::Init(HINSTANCE hInstance, int nCmdShow)
        {
            InitWindow(hInstance, nCmdShow);
            InitDevice();
            InitWorld();
            mbInit = true;
        }

        uint16_t Application::MainLoop()
        {

            MSG msg = {0};

            if (!mbInit)
            {
                //std::cout << "Plasmogrify Application: Init Not Complete.\n";
                MessageBox( NULL, "Plasmogrify: Init Not Complete.\n", "Error", MB_OK );

                return msg.wParam;
            }


            Timer timer;
            while(true)
            {
                if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);

                    if(msg.message == WM_QUIT)
                    {
                        break;
                    }

                    switch (msg.message)
                    {
                        case WM_ACTIVATE:
                        {
                            uint32_t i = 0;
                            uint32_t k = 2;
                            i += k;
                            break;
                        }
                        case WM_SIZE:
                        {
                            uint32_t i = 0;
                            uint32_t k = 2;
                            i += k;
                            break;
                        }
                        case WM_ENTERSIZEMOVE:
                        {
                            uint32_t i = 0;
                            uint32_t k = 2;
                            i += k;
                            break;
                        }
                    }

                }
                else
                {
                    timer.Tick();
                    mpWorldData->Update(timer.GetDeltaTime());

                    mpDevice->PreRender();
                    mpWorldData->Draw( mpDevice->GetRenderContext() );
                    mpDevice->PostRender();
                }
            }

            mpDevice->Cleanup();

            return msg.wParam;
        }

    } // namespace Application
} // namespace Plasmogrify