#pragma once
#include "Core/Window.h"

struct SDL_Window;

namespace GEngine
{

    class SDLWindow: public Window
    {
    public:

        SDLWindow() = default;
        NONCOPYABLE(SDLWindow);

        // Inherited via Window
        virtual void Initialize(const WindowProperties& winProp = WindowProperties{}) override;
        virtual void SwapBuffer() const override;
        virtual void ShutDown() override;
        virtual void SetTitle(const std::string& title) const override;

    private:
        SDL_Window* m_Window{};
        void* m_Context{};

    };
}
