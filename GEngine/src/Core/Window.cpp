#include "gepch.h"
#include "Core/Window.h"

#ifdef GENGINE_PLATFORM_WINDOWS
    #include "Windows/SDLWindow.h"  
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