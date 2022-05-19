//
// Created by JajaFil on 3/2/2022.
//

#ifndef TREMA_FILEDIALOG_H
#define TREMA_FILEDIALOG_H

#include <functional>
#include "../GuiElement.h"
#include "../IPopupComponent.h"
#include "../../ImGUI/Extensions/FileDialog/ImGuiFileBrowser.h"

namespace Trema::View
{
    enum FileDialogMode
    {
        Directory = 0,
        File = 1,
        Files = 2,
        SaveFile = 3,
    };

    class FileDialog : public IPopupComponent
    {
    public:
        FileDialog(std::string name);
        FileDialog(const FileDialog&) = delete;
        FileDialog& operator=(const FileDialog&) = delete;
        ~FileDialog() override;
        void Show() override;
        void ShowFileDialog(const std::string& base, std::string extensions, std::function<void(const std::string&)> listener, FileDialogMode mode = File);
        static std::shared_ptr<FileDialog> CreateFileDialog(std::string name);

    private:
        FileDialogMode m_mode;
        char* m_filePathBuffer = nullptr;
        bool m_display { false };
        std::string m_extension;
        std::function<void(const std::string&)> m_listener;
        std::unique_ptr<imgui_addons::ImGuiFileBrowser> m_fileDialog;

    };
}

#endif //TREMA_FILEDIALOG_H
