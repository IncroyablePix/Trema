//
// Created by JajaFil on 5/21/2022.
//

#include "Activity.h"
#include "../Windowing/Window.h"
#include "../Windowing/Fonts/FontsRepository.h"

namespace Trema::View
{
    Activity::Activity(Intent intent, std::shared_ptr<Window> window, uint16_t requestCode) :
        m_intent(std::move(intent)),
        m_window(std::move(window)),
        m_requestCode(requestCode)
    {

    }

    void Activity::OnActivityStart()
    {
    }

    void Activity::OnCreateView()
    {

    }

    void Activity::OnActivityEnd()
    {

    }

    void Activity::OnActivityResult(uint16_t requestCode, uint16_t resultCode, const Intent& intent)
    {

    }

    void Activity::OnActivityUpdate()
    {

    }

    std::string Activity::GetStringExtra(const std::string &name)
    {
        return m_intent.GetStringExtra(name);
    }

    uint64_t Activity::GetUint64Extra(const std::string &name)
    {
        return m_intent.GetUint64Extra(name);
    }

    uint32_t Activity::GetUint32Extra(const std::string &name)
    {
        return m_intent.GetUint32Extra(name);
    }

    uint16_t Activity::GetUint16Extra(const std::string &name)
    {
        return m_intent.GetUint16Extra(name);
    }

    uint8_t Activity::GetUint8Extra(const std::string &name)
    {
        return m_intent.GetUint8Extra(name);
    }

    int64_t Activity::GetInt64Extra(const std::string &name)
    {
        return m_intent.GetInt64Extra(name);
    }

    int32_t Activity::GetInt32Extra(const std::string &name)
    {
        return m_intent.GetInt32Extra(name);
    }

    int16_t Activity::GetInt16Extra(const std::string &name)
    {
        return m_intent.GetInt16Extra(name);
    }

    int8_t Activity::GetInt8Extra(const std::string &name)
    {
        return m_intent.GetInt8Extra(name);
    }

    float Activity::GetFloatExtra(const std::string &name)
    {
        return m_intent.GetFloatExtra(name);
    }

    double Activity::GetDoubleExtra(const std::string &name)
    {
        return m_intent.GetDoubleExtra(name);
    }

    bool Activity::GetBoolExtra(const std::string &name)
    {
        return m_intent.GetBoolExtra(name);
    }

    char8_t Activity::GetCharExtra(const std::string &name)
    {
        return m_intent.GetCharExtra(name);
    }

    void Activity::QuitApplication()
    {
        m_window->Close();
    }

    void Activity::SetLayout(std::shared_ptr<Layout> layout)
    {
        m_layout = std::move(layout);
    }

    void Activity::SetTopMenu(std::shared_ptr<TopMenu> topMenu)
    {
        m_menu = std::move(topMenu);
    }

    void Activity::LoadView(const std::string& path)
    {
        m_window->LoadView(path);
    }

    void Activity::ApplyStyle()
    {
        ImGuiStyle *style = &ImGui::GetStyle();

        style->WindowPadding = Style.GetWindowPadding();
        style->FramePadding = Style.GetFramePadding();
        style->WindowRounding = Style.GetWindowRounding();
        style->FrameRounding = Style.GetFrameRounding();

        //--- Colors
        style->Colors[ImGuiCol_Text] = Style.TextColor().GetColor();
        style->Colors[ImGuiCol_TextDisabled] = Style.TextDisabledColor().GetColor();
        style->Colors[ImGuiCol_WindowBg] = Style.WindowColor().GetColor();
        style->Colors[ImGuiCol_FrameBg] = Style.WidgetBackgroundColor().GetColor();
        style->Colors[ImGuiCol_FrameBgHovered] = Style.WidgetBackgroundColorHover().GetColor();
        style->Colors[ImGuiCol_FrameBgActive] = Style.WidgetBackgroundColorActive().GetColor();
        style->Colors[ImGuiCol_Button] = Style.ButtonColor().GetColor();
        style->Colors[ImGuiCol_ButtonHovered] = Style.ButtonColorHover().GetColor();
        style->Colors[ImGuiCol_ButtonActive] = Style.ButtonColorActive().GetColor();
        style->Colors[ImGuiCol_MenuBarBg] = Style.MenuBackgroundColor().GetColor();
        style->Colors[ImGuiCol_TitleBg] = Style.HeaderColor().GetColor();
        style->Colors[ImGuiCol_TitleBgActive] = Style.HeaderActiveColor().GetColor();
        style->Colors[ImGuiCol_TableHeaderBg] = Style.TableHeaderColor().GetColor();
        style->Colors[ImGuiCol_PopupBg] = Style.PopupBackgroundColor().GetColor();
        style->Colors[ImGuiCol_SliderGrab] = Style.SliderGrabColor().GetColor();
        style->Colors[ImGuiCol_SliderGrabActive] = Style.SliderGrabActiveColor().GetColor();

        if(!Style.GetFont().empty())
            SetDefaultFont(Style.GetFont());
    }

    void Activity::SetDefaultFont(const std::string &name)
    {
        m_window->SetDefaultFont(Style.GetFont());
    }
}