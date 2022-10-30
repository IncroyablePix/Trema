# Trema
Trema is a C++ framework for creating Graphical User Interfaces (GUIs) on Windows, Linux and macOS. It is based on the [Dear ImGUI library](https://github.com/ocornut/imgui) and uses [GLFW](https://www.glfw.org/) for window management.

Its main goal is to provide a simple and *modern* way of coding GUIs. It features an XML-based layout system, an Android-like Activity system and an lambda observer-listener events handling.

# Abstract
Have you ever had any consideration about GUI applications in C++? 
You basically need to pick either Qt or wxWidgets, which lack some features that are pleasant to have in modern solutions:
- Standard C++ libraries
- C++ 20 support
- XMake build system
- XML-based layout system
- Android-like Activity system
- Lambda-based events handling
- Familiar syntax and structure

**Since Dear ImGui stands for Immediate Mode GUI, the whole application will re-render for every frame. TL;DR => CPU & GPU Usage is greater than for Qt, wxWidgets, etc.**

# Features
Trema offers you to write full featured GUI applications with the view being only XML & Styling.
You can still use raw C++ components and add them manually to the GUI though.

A rough 10 lines of C++ code makes you able to open a rich GUI window fed by "TXML" and "TSS" files. 

Trema has its own styling language that goes by the name of TSS which has a CSS-like syntax with some extra stuff such as:
- Scoping/Nesting
- Variables
- ...

# Installation/Build
## Dependencies
Trema has several dependencies that are imported through XMake.
- [TinyXML](https://www.grinninglizard.com/tinyxml/) (Imported): Used for parsing XML files.
- [Dear ImGui](https://github.com/ocornut/imgui) (Imported): Used as backend between Trema and Vulkan for rendering GUI.
- [STB](https://github.com/nothings/stb) (Imported): Used for image loading.
- [GLFW](https://www.glfw.org/) (Imported): Used for window management.
- [Catch2](https://github.com/catchorg/Catch2) (Imported): Used for unit testing.
- [Vulkan](https://www.khronos.org/vulkan/) (Imported): Used for rendering GUI.

Though Vulkan headers are imported automatically, you need to install Vulkan for Trema to be able to run, otherwise, the program won't start at all.

## Actual build
Trema uses [XMake](https://xmake.io/) as build system. You can install it from the official website.
xmake is a a cross-platform build utility that handles all dependencies for you. It is also able to generate project files for Visual Studio, XCode, CMake, etc.
In order to build the project, you can run the following command in the project's directory:

```bash
xmake -w
```

This will build the project to the ```./build``` directory and offer the following tree:
```
build
└── (platform)
     ├── (arch)
         └── release
             ├── bin
             │    └── trema.[dll|so]
             ├── include
             │    └── Trema
             │        └── *.h
             ├── lib
             │   └── trema_lib.[lib|a]
             ├── include
             │    └── Trema
             ├── trema_sample
             │    └── resources
             │         ├── ...
             │         └── trema_sample[.exe]?
             └── trema_test
                 └── trema_test[.exe]?
```

The projects builds itself as a shared library and a static library. The static library is used for the sample and the test projects.

## CMake
For some IDEs such as JetBrains CLion, you might want to generate a CMake project. You can do so by running the following command:

```bash 
xmake project -k cmake
```

## Toolchains
This project has been tested with the following toolchains :

### Windows
- MinGW64     11.1.0
- MSVC x64    19.16.27043.0

I would personally recommend to use MSVC on Windows since it doesn't require to provide any extra .dll with deployed version but MinGW is fine too.

### Linux
- g++   

### MacOS
- none
