//
// Created by JajaFil on 3/2/2022.
//

#include "FileDialog.h"
#include "../../ImGUI/Extensions/FileDialog/ImGuiFileBrowser.h"
#include "../../ImGUI/imgui.h"
#include <sstream>
#include <utility>

#define FILE_PATH_BUFFER_SIZE               (512)

namespace Trema::View
{
    FileDialog::FileDialog(std::string name) :
        IPopupComponent(std::move(name)),
        m_filePathBuffer(new char[FILE_PATH_BUFFER_SIZE]),
        m_fileDialog(std::make_unique<imgui_addons::ImGuiFileBrowser>())
    {

    }

    FileDialog::~FileDialog()
    {

    }

    void FileDialog::ShowFileDialog(const std::string &base, std::string extensions, std::function<void(const std::string &)> listener, FileDialogMode mode)
    {
        m_listener = std::move(listener);
        m_extension = std::move(extensions);
        m_mode = mode;
        m_display = true;
    }

    void FileDialog::Show()
    {
        auto type = imgui_addons::ImGuiFileBrowser::DialogMode::OPEN;

        switch(m_mode)
        {
            case Directory:
                type = imgui_addons::ImGuiFileBrowser::DialogMode::SELECT;
                break;
            case File:
            case Files:
                type = imgui_addons::ImGuiFileBrowser::DialogMode::OPEN;
                break;
            case SaveFile:
                type = imgui_addons::ImGuiFileBrowser::DialogMode::SAVE;
                break;
        }

        if(m_fileDialog->showFileDialog(NameId(), type, ImVec2(700, 310), m_extension))
        {
            if(m_listener)
                m_listener(m_fileDialog->selected_path);
        }

        if(m_display)
        {
            ImGui::OpenPopup(NameId());
            m_display = false;
        }
    }

    std::shared_ptr<FileDialog> FileDialog::CreateFileDialog(std::string name)
    {
        return std::make_shared<FileDialog>(std::move(name));
    }
}