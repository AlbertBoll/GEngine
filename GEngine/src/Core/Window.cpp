#include "gepch.h"
#include "Core/Window.h"

#ifdef GENGINE_PLATFORM_WINDOWS
    #include "Windows/SDLWindow.h"  

    class SDLWindowCustomDeleter
    {
    public:
        void operator()(GEngine::SDLWindow* window)const
        {
            window->ShutDown();
            delete window;
            window = nullptr;
        }


    };

#endif



namespace GEngine
{


    ScopedPtr<Window> Window::Create(const WindowProperties& winProp)
    {
        #ifdef GENGINE_PLATFORM_WINDOWS
     
            return CreateScopedPtr<SDLWindow>();

        #else
            ASSERT(false, "Didn't support platform other than windows");

        #endif


    }

}