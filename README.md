
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
- Font: Loads a fond into the program's memory.
  - src: Source file for the Font (.ttf files)
  - size: Size of the font
  - name: The name that will be used later on to retrieve the font as a style
  - *content*: None
- Style: Loads a stylesheet and applies it *after all elements have been loaded*.
  - src: The source file for the stylesheet
  - *content*: Instead of a source file, you can inline the stylesheet code
- Title: Sets the title of the window. The last Title element will be applied.
  - *content*: The title string

## Body


