cmake_minimum_required(VERSION 3.20)
project(Trema_Tests)

set(CMAKE_CXX_STANDARD 20)


############ TESTING ############
find_package(Catch2 3 REQUIRED)
add_executable(${PROJECT_NAME}
        Tests.cpp
        View/Style/TokenizerTests/TokenizerTests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
include(ParseAndAddCatchTests)
catch_discover_tests(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${Vulkan_INCLUDE_DIR}
        PUBLIC ${SDL2_INCLUDE_DIRS})