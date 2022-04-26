#include "gepch.h"
#include "Core/BaseApp.h"

namespace GEngine
{
    BaseApp::~BaseApp()
    {

    }

    void BaseApp::Initialize()
    {
        m_GEngine.Initialize();
    }

    void BaseApp::AddWindows(const WindowProperties& winProp)
    {
        m_GEngine.AddWindows(winProp);
    }

    void BaseApp::AddWindows(const std::initializer_list<WindowProperties>& winProps)
    {
        m_GEngine.AddWindows(winProps);
    }

    void BaseApp::Run()
    {
        m_GEngine.Run();
    }
}
