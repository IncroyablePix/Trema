cmake_minimum_required(VERSION 3.20)
project(Trema)
set(PROJECT_TEST "Trema_Tests")

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

###
set(PROJECT_FILES
        Src/View/ImGUI/imconfig.h Src/View/ImGUI/imgui.h Src/View/ImGUI/imgui.cpp Src/View/ImGUI/imgui_demo.cpp Src/View/ImGUI/imgui_draw.cpp Src/View/ImGUI/imgui_impl_sdl.h Src/View/ImGUI/imgui_impl_sdl.cpp Src/View/ImGUI/imgui_impl_vulkan.h Src/View/ImGUI/imgui_impl_vulkan.cpp Src/View/ImGUI/imgui_internal.h Src/View/ImGUI/imgui_tables.cpp Src/View/ImGUI/imgui_widgets.cpp Src/View/ImGUI/imstb_rectpack.h Src/View/ImGUI/imstb_textedit.h Src/View/ImGUI/imstb_truetype.h Src/View/SDL2/SDL2Window.cpp Src/View/SDL2/SDL2Window.h Src/View/Vulkan/VulkanRenderer.cpp Src/View/Vulkan/VulkanRenderer.h Src/View/WindowInitializationException.cpp Src/View/WindowInitializationException.h Src/View/IWindow.cpp Src/View/IWindow.h
        Src/View/ImGUI/Extensions/FileDialog/ImGuiFileBrowser.h Src/View/ImGUI/Extensions/FileDialog/ImGuiFileBrowser.cpp Src/View/ImGUI/Extensions/FileDialog/dirent.h
        Src/View/Parser/TinyXML/tinystr.cpp Src/View/Parser/TinyXML/tinystr.h Src/View/Parser/TinyXML/tinyxml.cpp Src/View/Parser/TinyXML/tinyxml.h Src/View/Parser/TinyXML/tinyxmlerror.cpp Src/View/Parser/TinyXML/tinyxmlparser.cpp
        Src/View/Components/Layout/Docking/DockSpace.h Src/View/Components/Layout/Docking/DockSpace.cpp Src/View/Components/Layout/Docking/MainDockSpace.h Src/View/Components/Layout/Docking/MainDockSpace.cpp Src/View/Components/IGuiElement.h Src/View/Components/Container/IContainer.cpp Src/View/Components/Container/IContainer.h Src/View/Components/Layout/ILayout.cpp Src/View/Components/Layout/ILayout.h Src/View/Components/Container/WindowContainer.cpp Src/View/Components/Container/WindowContainer.h Src/View/Components/TopMenu/TopMenu.cpp Src/View/Components/TopMenu/TopMenu.h Src/View/Components/Widgets/Button.cpp Src/View/Components/Widgets/Button.h Src/View/Components/Widgets/Options/Radio.cpp Src/View/Components/Widgets/Options/Radio.h Src/View/Components/Widgets/Options/Combo.cpp Src/View/Components/Widgets/Options/Combo.h Src/View/Components/Widgets/Text.cpp Src/View/Components/Widgets/Text.h Src/View/Components/Widgets/Checkbox.cpp Src/View/Components/Widgets/Checkbox.h Src/View/Components/Widgets/Table.cpp Src/View/Components/Widgets/Table.h Src/View/Components/IGuiElement.cpp Src/View/Components/Widgets/Input/TextInput.cpp Src/View/Components/Widgets/Input/TextInput.h Src/View/Components/Widgets/Input/TextArea.cpp Src/View/Components/Widgets/Input/TextArea.h Src/View/Parser/IViewParser.cpp Src/View/Parser/IViewParser.h Src/View/Parser/TinyXML/TinyXMLViewParser.cpp Src/View/Parser/TinyXML/TinyXMLViewParser.h Src/View/Exceptions/ParsingException.cpp Src/View/Exceptions/ParsingException.h Src/View/Components/Widgets/Options/SelectorOption.cpp Src/View/Components/Widgets/Options/SelectorOption.h Src/View/Components/Widgets/DisplayException.cpp Src/View/Components/Widgets/DisplayException.h Src/View/Components/Widgets/FamilyException.cpp Src/View/Components/Widgets/FamilyException.h Src/View/Components/Windows/FileDialog.cpp Src/View/Components/Windows/FileDialog.h Src/View/Components/IPopupComponent.cpp Src/View/Components/IPopupComponent.h Src/View/Utils/FileSplits.cpp Src/View/Utils/FileSplits.h Src/View/Utils/StringExtensions.cpp Src/View/Utils/StringExtensions.h Src/View/Components/ElementStyle.cpp Src/View/Components/ElementStyle.h Src/View/Style/IStyleParser.cpp Src/View/Style/IStyleParser.h Src/View/Style/StackedStyleParser.cpp Src/View/Style/StackedStyleParser.h Src/View/Style/Tokenizer/Tokenizer.cpp Src/View/Style/Tokenizer/Tokenizer.h Src/View/Exceptions/FileNotFoundException.cpp Src/View/Exceptions/FileNotFoundException.h Src/View/Style/SymbolTable.cpp Src/View/Style/SymbolTable.h Src/View/Components/TopMenu/SubMenu.cpp Src/View/Components/TopMenu/SubMenu.h Src/View/Components/TopMenu/MenuOption.cpp Src/View/Components/TopMenu/MenuOption.h Src/View/Components/Widgets/Separator.cpp Src/View/Components/Widgets/Separator.h Src/View/Components/Layout/StackSpace/StackSpace.cpp Src/View/Components/Layout/StackSpace/StackSpace.h Src/View/Components/Layout/LayoutException.cpp Src/View/Components/Layout/LayoutException.h Src/View/Style/Variable.cpp Src/View/Style/Variable.h Src/View/Style/StyleApplier.cpp Src/View/Style/StyleApplier.h Src/View/Components/Widgets/SliderFloat.cpp Src/View/Components/Widgets/SliderFloat.h Src/View/Style/CompilationMistake.cpp Src/View/Style/CompilationMistake.h Src/View/Style/Tokenizer/ITokenizer.cpp Src/View/Style/Tokenizer/ITokenizer.h Src/View/Style/Tokenizer/Token.cpp Src/View/Style/Tokenizer/Token.h)

############ TESTING ############
find_package(Catch2 3 REQUIRED)
add_executable(${PROJECT_TEST}
        Test/Tests.cpp
        Test/View/Style/TokenizerTests/TokenizerTests.cpp
        ${PROJECT_FILES})
target_link_libraries(${PROJECT_TEST} PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
catch_discover_tests(${PROJECT_TEST})

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

add_executable(${PROJECT_NAME} Src/main.cpp ${PROJECT_FILES})

############ LINK ############
message("Linking...")

target_include_directories(${PROJECT_NAME}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS})

target_include_directories(${PROJECT_TEST}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS})

### Windows
if(OS STREQUAL "NT")
    message("Linking Windows specifics...")
    target_link_libraries(${PROJECT_NAME} PUBLIC -lmingw32) # -mwindows
    add_definitions(-DSDL_MAIN_HANDLED)

    target_link_libraries(${PROJECT_TEST} PUBLIC -lmingw32) # -mwindows
    add_definitions(-DSDL_MAIN_HANDLED)
endif()

### SDL 2 ###
message("Linking SDL2...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_TEST} PUBLIC ${SDL2_LIBRARIES})

### Vulkan ###
message("Linking Vulkan...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES})
target_link_libraries(${PROJECT_TEST} PUBLIC ${Vulkan_LIBRARIES})

### MinGW ###
target_link_options(${PROJECT_NAME} PUBLIC -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_TEST} PUBLIC -static-libgcc -static-libstdc++)