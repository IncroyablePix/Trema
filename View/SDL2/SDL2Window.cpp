//
// Created by JajaFil on 2/12/2022.
//

#include <sstream>
#include <SDL2/SDL_vulkan.h>
#include "SDL2Window.h"
#include "../WindowInitializationException.h"
#include "../ImGUI/imgui_impl_sdl.h"

namespace Trema::View
{
    SDL2Window::SDL2Window(const WindowInfo &info) :
            IWindow(info),
            m_window(CreateWindow(info)),
            m_renderer(info, m_window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void) io;
        io.Fonts->AddFontDefault();

        io.DisplaySize.x = static_cast<float>(m_width);
        io.DisplaySize.y = static_cast<float>(m_height);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsLight();
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        m_renderer.Init(m_window);
        m_renderer.LoadFonts();
    }

    SDL2Window::~SDL2Window()
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void SDL2Window::InitializeSdl2()
    {
        if(!Sdl2Initialized)
        {
            if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
            {
                std::stringstream ss;
                ss << "Error during SDL2 initialization: " << SDL_GetError();
                throw WindowInitializationException(ss.str().c_str());
            }

            Sdl2Initialized = true;
        }
    }

    void SDL2Window::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    void SDL2Window::PollEvent()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if(event.type == SDL_QUIT)
            {
                m_opened = false;
            }
            else if(event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(m_window))
            {
                m_opened = false;
            }
        }

        m_renderer.ResizeSwapChain(m_window);
        /* */
    }

    bool SDL2Window::IsOpened()
    {
        return m_opened;
    }

    void SDL2Window::Update()
    {
        PollEvent();

        Render();
    }

    void SDL2Window::Render()
    {
        bool show_demo_window;
        auto* wd = m_renderer.GetWindowData();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();

        if(m_standardFont)
            ImGui::PushFont(m_standardFont);

        //--- ImGui code
        if(m_menu)
            m_menu->Show();
        if(m_layout)
            m_layout->Show();
        for(const auto& [name, popup] : m_popupComponents)
            popup->Show();
        //---

        if(m_standardFont)
            ImGui::PopFont();

        ImGui::Render();
        ImDrawData* drawData = ImGui::GetDrawData();

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        const bool isMinimized = (drawData->DisplaySize.x <= 0.0f || drawData->DisplaySize.y <= 0.0f);
        if(!isMinimized)
        {
            m_renderer.Clear();
            m_renderer.Render(wd, drawData);
            m_renderer.FramePresent(wd);
        }
    }

    SDL_Window *SDL2Window::CreateWindow(const WindowInfo &info)
    {
        InitializeSdl2();
        return SDL_CreateWindow(info.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.Width, info.Height, WindowFlags);
    }

    int SDL2Window::Run()
    {
        m_opened = true;
        Build();
        while(IsOpened())
        {
            Update();
        }

        return 0;
    }

    std::shared_ptr<SDL2Window> SDL2Window::CreateSDL2Window(const WindowInfo &info)
    {
        return std::make_shared<SDL2Window>(info);
    }
}