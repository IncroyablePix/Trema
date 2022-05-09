//
// Created by JajaFil on 5/9/2022.
//

#include "FontsRepository.h"
#include "../../Utils/FileSplits.h"

namespace Trema::View
{
    FontsRepository *FontsRepository::Instance = nullptr;

    FontsRepository::FontsRepository() = default;
    FontsRepository::~FontsRepository() = default;

    FontsRepository *FontsRepository::GetInstance()
    {
        if(!Instance)
            Instance = new FontsRepository;

        return Instance;
    }

    void FontsRepository::AddFont(std::string name, std::string path, float size, ImFontConfig* fontConfig)
    {
        if(m_fonts.find(name) == m_fonts.end())
        {
            FontData fontData = {.Path = std::move(
                    path), .Size = size, .FontConfig = fontConfig };

            fontData.Upload();

            if(name.empty())
            {
                m_fonts[FileSplit(fontData.Path).FileWithoutExtension] = fontData;
            }
            else
            {
                m_fonts[std::move(name)] = fontData;
            }
        }
    }

    void FontsRepository::ReloadFonts()
    {
        for(auto& [name, fontData] : m_fonts)
        {
            fontData.Upload();
        }
    }

    FontData &FontsRepository::operator[](const std::string& name)
    {
        return m_fonts[name];
    }

    bool FontsRepository::Exists(const std::string &name)
    {
        return m_fonts.find(name) != m_fonts.end();
    }

    void FontData::Upload()
    {
        static const ImWchar ranges[] =
        {
                0x0020, 0x00FF, // Basic Latin + Latin Supplement
                0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
                0x20AC, 0x20AC, // €
                0x2122, 0x2122, // ™
                0x2196, 0x2196, // ↖
                0x21D6, 0x21D6, // ⇖
                0x2B01, 0x2B01, // ⬁
                0x2B09, 0x2B09, // ⬉
                0x2921, 0x2922, // ⤡ ⤢
                0x263A, 0x263A, // ☺
                0x266A, 0x266A, // ♪
                0x2DE0, 0x2DFF, // Cyrillic Extended-A
                0xA640, 0xA69F, // Cyrillic Extended-B
                0,
        };

        ImGuiIO& io = ImGui::GetIO();
        auto font = io.Fonts->AddFontFromFileTTF(Path.c_str(), Size, FontConfig, ranges);
        Font = font;
    }
}
