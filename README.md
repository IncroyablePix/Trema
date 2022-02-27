
# Trema
ImGUI wrapper with XML view descriptors

# Abstract
Have you ever had any consideration about GUI applications in C++? 
Trema is a wrapper around Dear ImGui that allows to write views as XML files. It uses SDL2 & Vulkan as backend, Dear ImGui for components and TinyXML for XML fiiles parsing.

**Since Dear ImGui stands for Immediate Mode GUI, the whole application will re-render for every frame. TL;DR => CPU & GPU Usage is greater than for Qt, wxWidgets, etc.**

