cmake_minimum_required(VERSION 3.20)
project(Trema)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES} View/Components/Widgets/CollectionView/VectorView.cpp View/Components/Widgets/CollectionView/VectorView.h)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

############ DEPENDENCIES ############
### Vulkan ###
message("Including VULKAN...")
find_package(Vulkan REQUIRED FATAL_ERROR)
message("Done!")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY RULE_LAUNCH_COMPILE "\"${CMAKE_COMMAND}\" -E time")
set_property(TARGET ${PROJECT_NAME} PROPERTY RULE_LAUNCH_LINK "\"${CMAKE_COMMAND}\" -E time")

############ COPYING HEADERFILES ############
file(COPY .
        DESTINATION ${CMAKE_BINARY_DIR}/include
        FILES_MATCHING
        PATTERN *.h
        )

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

