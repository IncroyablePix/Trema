//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_IGUIELEMENT_H
#define MATH4BG_IGUIELEMENT_H

#include <memory>
#include "Style/ElementStyle.h"

namespace Trema::View
{
    class IGuiElement : public std::enable_shared_from_this<IGuiElement>
    {
    public:
        IGuiElement(std::shared_ptr<IGuiElement> parent, std::string name);

        virtual void Show() = 0;
        virtual const std::string& GetName();
        inline const std::string& GetId() { return m_id; }
        inline void SetId(std::string id) { m_id = std::move(id); }
        virtual const char* NameId();
        virtual void SetName(std::string name);
        virtual void BeginStyle();
        virtual void EndStyle();

        virtual ImVec2 GetItemSize() const;

        inline void SetDockSize(float dockSize) { m_dockSize = dockSize; }
        inline float GetDockSize() const { return m_dockSize; }

        ElementStyle Style;

    protected:
        template<class T>
        inline static bool IsType(const std::shared_ptr<IGuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }
        template<class T>
        inline static std::shared_ptr<T> CastTo(const std::shared_ptr<IGuiElement> &element) { return std::dynamic_pointer_cast<T>(element); }
        
        std::shared_ptr<IGuiElement> m_parent;
        float m_dockSize { 0.2f };
        std::string m_name;
        std::string m_id;
        unsigned int m_styles;
        unsigned int m_colors;
    };
}

#endif //MATH4BG_IGUIELEMENT_H
