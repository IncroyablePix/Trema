//
// Created by JajaFil on 2/12/2022.
//

#ifndef TREMA_SDL2WINDOW_H
#define TREMA_SDL2WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include "../IWindow.h"
#include "../Vulkan/VulkanRenderer.h"

namespace Trema::View
{
    class SDL2Window : public IWindow
    {
    public:
        explicit SDL2Window(const WindowInfo &info);
        ~SDL2Window();
        void Resize(int width, int height) override;
        void PollEvent() override;
        int Run() override;
        bool IsOpened() override;
        void Update() override;
        void Render() override;
        void UploadFonts();
        void SetTitle(const std::string &title) override;

        static std::shared_ptr<SDL2Window> CreateSDL2Window(const WindowInfo &info);

    private:

        bool m_opened;
        SDL_Window* m_window;
        VulkanRenderer m_renderer;

        static void InitializeSdl2();

        static SDL_Window* CreateWindow(const WindowInfo &info);
    };
    static SDL_WindowFlags WindowFlags = (SDL_WindowFlags) (SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    static bool Sdl2Initialized { false };
}

#endif //TREMA_SDL2WINDOW_H
