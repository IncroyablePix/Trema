cmake_minimum_required(VERSION 3.20)
project(Trema)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES} View/Components/Widgets/Sliders/SliderInt.cpp View/Components/Widgets/Sliders/SliderInt.h)

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
    set(BITS 32)
endif()

############ DEPENDENCIES ############
### SDL2 ###
message("Including SDL2...")

if(NOT DEFINED SDL2_ROOT AND
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

add_library(${PROJECT_NAME} SHARED ${SOURCES})

############ LINK ############
message("Linking...")

target_include_directories(${PROJECT_NAME}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS})

### SDL 2 ###
message("Linking SDL2...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})

if(OS STREQUAL "NT")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIBRARIES}" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

### Vulkan ###
message("Linking Vulkan...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES})


