//
// Created by JajaFil on 5/9/2022.
//

#ifndef TREMA_PROJECT_FONTSREPOSITORY_H
#define TREMA_PROJECT_FONTSREPOSITORY_H

#include <string>
#include "../../ImGUI/imgui.h"
#include <unordered_map>

namespace Trema::View
{
    struct FontData
    {
        std::string Path;
        float Size;
        ImFontConfig *FontConfig;
        ImWchar *GlyphRanges;
        ImFont* Font;

        void Upload();
    };

    class FontsRepository
    {
    private:
        static FontsRepository* Instance;
        FontsRepository();
        ~FontsRepository();
        std::unordered_map<std::string, FontData> m_fonts;

    public:
        FontsRepository operator=(const FontsRepository&) = delete;
        explicit FontsRepository(const FontsRepository&) = delete;
        static FontsRepository* GetInstance();

        void AddFont(std::string name, std::string path, float size, ImFontConfig* fontConfig);

        void ReloadFonts();
        FontData& operator[](const std::string& name);
        bool Exists(const std::string& name);
    };
}

#endif //TREMA_PROJECT_FONTSREPOSITORY_H
