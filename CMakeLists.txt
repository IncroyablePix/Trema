cmake_minimum_required(VERSION 3.20)
project(Trema)

set(CMAKE_CXX_STANDARD 20)

### Platform ###
if(WIN64 OR WIN32)
    set(OS NT)
elseif(UNIX)
    set(OS UNIX)
elseif(APPLE)
    set(OS MAC)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(BITS 32)
endif()

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

############ DEPENDENCIES ############
### SDL2 ###
message("Including SDL2...")

if(NOT DEFINED     SDL2_ROOT  AND
        NOT DEFINED $ENV{SDL2_ROOT})
    set(SDL2_ROOT "$ENV{SDL2}")
endif()

if(OS STREQUAL "NT")
    if (BITS MATCHES 64)
        set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/x86_64-w64-mingw32/include")
        set(SDL2_LIBRARIES "${SDL2_ROOT}/x86_64-w64-mingw32/bin/SDL2.dll")
    else (BITS MATCHES 32)
        set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/i686-w64-mingw32/include")
        set(SDL2_LIBRARIES "${SDL2_ROOT}/i686-w64-mingw32/bin/SDL2.dll")
    endif ()
elseif(OS STREQUAL "UNIX")
    find_package(SDL2 REQUIRED)
endif()

message("Done!")

### Vulkan ###
message("Including VULKAN...")
find_package(Vulkan REQUIRED FATAL_ERROR)
message("Done!")


# OS SPECIFICITIES
message("Compiling for : ")

if(OS STREQUAL "NT")
    list(APPEND SRC_FILES res.rc)
    message("Windows")
elseif(OS STREQUAL "UNIX")
    message("UNIX")
elseif(OS STREQUAL "MAC")
    list(APPEND SRC_FILES ../../src/osx/carbon/wxmac.icns)
    message("MacOS")
endif()

if(BITS MATCHES 64)
    message("64bits")
elseif(BITS MATCHES 32)
    message("32bits")
endif()

add_executable(${PROJECT_NAME}
        main.cpp
        View/ImGUI/imconfig.h View/ImGUI/imgui.h View/ImGUI/imgui.cpp View/ImGUI/imgui_demo.cpp View/ImGUI/imgui_draw.cpp View/ImGUI/imgui_impl_sdl.h View/ImGUI/imgui_impl_sdl.cpp View/ImGUI/imgui_impl_vulkan.h View/ImGUI/imgui_impl_vulkan.cpp View/ImGUI/imgui_internal.h View/ImGUI/imgui_tables.cpp View/ImGUI/imgui_widgets.cpp View/ImGUI/imstb_rectpack.h View/ImGUI/imstb_textedit.h View/ImGUI/imstb_truetype.h View/SDL2/SDL2Window.cpp View/SDL2/SDL2Window.h View/Vulkan/VulkanRenderer.cpp View/Vulkan/VulkanRenderer.h View/WindowInitializationException.cpp View/WindowInitializationException.h View/IWindow.cpp View/IWindow.h
        View/ImGUI/Extensions/FileDialog/ImGuiFileBrowser.h View/ImGUI/Extensions/FileDialog/ImGuiFileBrowser.cpp View/ImGUI/Extensions/FileDialog/dirent.h
        View/Parser/TinyXML/tinystr.cpp View/Parser/TinyXML/tinystr.h View/Parser/TinyXML/tinyxml.cpp View/Parser/TinyXML/tinyxml.h View/Parser/TinyXML/tinyxmlerror.cpp View/Parser/TinyXML/tinyxmlparser.cpp
        View/Components/Layout/Docking/DockSpace.h View/Components/Layout/Docking/DockSpace.cpp View/Components/Layout/Docking/MainDockSpace.h View/Components/Layout/Docking/MainDockSpace.cpp View/Components/IGuiElement.h View/Components/Container/IContainer.cpp View/Components/Container/IContainer.h View/Components/Layout/ILayout.cpp View/Components/Layout/ILayout.h View/Components/Container/WindowContainer.cpp View/Components/Container/WindowContainer.h View/Components/TopMenu/TopMenu.cpp View/Components/TopMenu/TopMenu.h View/Components/Widgets/Button.cpp View/Components/Widgets/Button.h View/Components/Widgets/Options/Radio.cpp View/Components/Widgets/Options/Radio.h View/Components/Widgets/Options/Combo.cpp View/Components/Widgets/Options/Combo.h View/Components/Widgets/Text.cpp View/Components/Widgets/Text.h View/Components/Widgets/Checkbox.cpp View/Components/Widgets/Checkbox.h View/Components/Widgets/Table.cpp View/Components/Widgets/Table.h View/Components/IGuiElement.cpp View/Components/Widgets/Input/TextInput.cpp View/Components/Widgets/Input/TextInput.h View/Components/Widgets/Input/TextArea.cpp View/Components/Widgets/Input/TextArea.h View/Parser/IViewParser.cpp View/Parser/IViewParser.h View/Parser/TinyXML/TinyXMLViewParser.cpp View/Parser/TinyXML/TinyXMLViewParser.h View/Exceptions/ParsingException.cpp View/Exceptions/ParsingException.h View/Components/Widgets/Options/SelectorOption.cpp View/Components/Widgets/Options/SelectorOption.h View/Components/Widgets/DisplayException.cpp View/Components/Widgets/DisplayException.h View/Components/Widgets/FamilyException.cpp View/Components/Widgets/FamilyException.h View/Components/Windows/FileDialog.cpp View/Components/Windows/FileDialog.h View/Components/IPopupComponent.cpp View/Components/IPopupComponent.h View/Utils/FileSplits.cpp View/Utils/FileSplits.h View/Utils/StringExtensions.cpp View/Utils/StringExtensions.h View/Components/ElementStyle.cpp View/Components/ElementStyle.h View/Style/IStyleParser.cpp View/Style/IStyleParser.h View/Style/StackedStyleParser.cpp View/Style/StackedStyleParser.h View/Style/Tokenizer.cpp View/Style/Tokenizer.h View/Exceptions/FileNotFoundException.cpp View/Exceptions/FileNotFoundException.h View/Style/SymbolTable.cpp View/Style/SymbolTable.h View/Components/TopMenu/SubMenu.cpp View/Components/TopMenu/SubMenu.h View/Components/TopMenu/MenuOption.cpp View/Components/TopMenu/MenuOption.h View/Components/Widgets/Separator.cpp View/Components/Widgets/Separator.h View/Components/Layout/StackSpace/StackSpace.cpp View/Components/Layout/StackSpace/StackSpace.h View/Components/Layout/LayoutException.cpp View/Components/Layout/LayoutException.h View/Style/Variable.cpp View/Style/Variable.h View/Style/StyleApplier.cpp View/Style/StyleApplier.h)

############ LINK ############
message("Linking...")

target_include_directories(${PROJECT_NAME}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS})

### Windows
if(OS STREQUAL "NT")
    message("Linking Windows specifics...")
    target_link_libraries(${PROJECT_NAME} PUBLIC -lmingw32) # -mwindows
    add_definitions(-DSDL_MAIN_HANDLED)
endif()

### SDL 2 ###
message("Linking SDL2...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})

### Vulkan ###
message("Linking Vulkan...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES})

### MinGW ###
target_link_options(${PROJECT_NAME} PUBLIC -static-libgcc -static-libstdc++)