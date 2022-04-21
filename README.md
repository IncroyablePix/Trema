
# Trema
ImGUI wrapper with XML view descriptors

# Abstract
Have you ever had any consideration about GUI applications in C++? 
Trema is a wrapper around Dear ImGui that allows to write views as XML files. It uses SDL2 & Vulkan as backend, Dear ImGui for components and TinyXML for XML fiiles parsing.

**Since Dear ImGui stands for Immediate Mode GUI, the whole application will re-render for every frame. TL;DR => CPU & GPU Usage is greater than for Qt, wxWidgets, etc.**

# Features
Trema offers you to write full featured GUI applications with the view being only XML & Styling.
You can still use raw C++ components and add them manually to the GUI though.

A rough 10 lines of C++ code makes you able to open a rich GUI window fed by "TXML" and "TSS" files. 

Trema has its own styling language that goes by the name of TSS which has a CSS-like syntax with some extra stuff such as:
- Scoping/Nesting
- Variables
- ...

# TXML
The TXML which stands for Trema XML is used to create GUI applications. It roughly follows some kind of HTML structure. 
At root we have a **App** element which contains everything else.
As children, **App** allows only **Head** and **Body** elements which are very specifically defined.

## Head
Head is an element that will contain resource loading, global description and metadata about the application.
It allows the following elements as children:

### Descriptors
#### Font
Loads a fond into the program's memory.
- src: Source file for the Font (.ttf files)
- size: Size of the font
- name: The name that will be used later on to retrieve the font as a style
- *content*: None

#### Style
Loads a stylesheet and applies it *after all elements have been loaded*.
- src: The source file for the stylesheet
- *content*: Instead of a source file, you can inline the stylesheet code

#### Title
Sets the title of the window. The last Title element will be applied.
- *content*: The title string

### Body
Body is an element that will contain the actual elements. 
Right under the **body**, you need to have a *Layout* which will contain the different elements.
Be careful that **each element** on a same level should have a different *name*. A name acts as an identifier.

It allows the following elements as children:

### Layouts
Layouts allow *containers* as children. They fit element containers in the window.

#### MainDockSpace
A dock-space is a layout that allows you to move the different sub-windows around. 
It also allows you to take the sub-windows out of the main window.

- name: The name of the element.
- saveLayout: The layout should be saved and the custom user settings for docking should override the programmed layout.
- *content*: Containers

#### StackSpace
A stack-space is a simple type of layout in which elements are just stacked one under the other.

- name: The name of the element.
- *content*: Containers

### Containers
A container is what the name is: it contains elements.

#### TopMenu
TopMenu is a special container that should appear only once in your layout. It consists in the top menu bar of the window.
TopMenu allows only one child, which is *SubMenu*.
- *content*: SubMenus

#### SubMenu
Can only be child of a *TopMenu*. Represents a "column" from the TopMenu.
It allows only *MenuOption* type elements.

- name: The name of the submenu that will be displayed.
- *content*: MenuOptions

#### WindowContainer
WindowContainer is a container that allows all simple gui elements. It defaults by stacking them from top to bottom.

- name: The name of the window that will be displayed on top.
- *content*: Elements

### Elements
Elements could also go by the name of widgets. They can only be a member of a container. 

#### MenuOption
MenuOption is an option for SubMenu. A menu option represents an option that can be clicked on.

- name: The name of the option that will be displayed.
- shortcut: The shortcut that will be displayed.

#### Radio
Radio is a "menu" consisting of mutually exclusive options.
It allows only *Option* elements.

- name:
- *content*: The title string

#### Combo

#### Option
#### Button
#### Text
#### Checkbox
#### Table
#### TableRow
#### TextInput
#### TextArea
#### Separator
#### SliderFloat

# TSS

# Example codes

```cpp

```