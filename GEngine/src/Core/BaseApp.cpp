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


    void BaseApp::Run()
    {
        m_GEngine.Run();
    }
}
