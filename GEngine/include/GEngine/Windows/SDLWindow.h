#pragma once
#include "Core/Window.h"

struct SDL_Window;

namespace GEngine
{


    class SDLWindow: public Window//public WindowImpl<SDLWindow>
    {
    public:

        SDLWindow() = default;
        NONCOPYABLE(SDLWindow);

        // Inherited via Window
        virtual void Initialize(const WindowProperties& winProp = WindowProperties{}) override;
        virtual void SwapBuffer() const override;
        virtual void ShutDown() override;
        virtual void SetTitle(const std::string& title) const override;

        // Inherited via Window
        virtual uint32_t GetWindowID() const override;
        
        //operator SDL_Window* () { return m_Window; }

    private:
        void SetWindow(int DisplayWidth, int DisplayHeight, uint32_t flag, const WindowProperties& winProp = WindowProperties{});
        uint32_t GetWindowFlag(const WindowProperties& winProp);

    private:
        SDL_Window* m_Window{};
        void* m_Context{};


      


        // Inherited via Window
        virtual void BeginRender() const override;

        virtual void EndRender() const override;


        // Inherited via Window
        virtual std::string GetTitle() const override;

    };
}
