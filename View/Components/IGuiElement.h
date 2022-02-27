//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_IGUIELEMENT_H
#define MATH4BG_IGUIELEMENT_H

#include <memory>

namespace Trema::View
{
    enum Orientation
    {
        Column,
        Row
    };

    struct ElementStyle
    {
        Orientation Orientation = Row;
    };

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

        inline void SetDockSize(float dockSize) { m_dockSize = dockSize; }
        inline float GetDockSize() const { return m_dockSize; }

        ElementStyle Style;

    protected:
        template<class T>
        inline static bool IsType(const std::shared_ptr<IGuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }
        
        std::shared_ptr<IGuiElement> m_parent;
        float m_dockSize { 0.2f };
        std::string m_name;
        std::string m_id;
    };
}

#endif //MATH4BG_IGUIELEMENT_H
