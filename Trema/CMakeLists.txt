cmake_minimum_required(VERSION 3.20)
project(Trema)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


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
### Vulkan ###
message("Including VULKAN...")
set(ENV{VULKAN_SDK} $ENV{VK_SDK_PATH})
find_package(Vulkan REQUIRED FATAL_ERROR)
message("Done!")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

############ LINK ############
message("Linking...")

target_include_directories(${PROJECT_NAME}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS}
        PUBLIC ../glfw-3.3.7/src)

### Vulkan ###
message("Linking Vulkan...")
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES})

### GLFW ###
message("Linking GLFW...")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

