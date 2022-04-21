cmake_minimum_required(VERSION 3.20)
project(Trema_Sample)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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

###
set(PROJECT_FILES
        ../main.cpp)

### Testing
add_subdirectory(Trema)
add_subdirectory(Test)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

### Trema ###
message("Linking Trema...")
target_link_libraries(${PROJECT_NAME} PUBLIC Trema)

### Windows
if(OS STREQUAL "NT")
    message("Linking Windows specifics...")
    target_link_libraries(${PROJECT_NAME} PUBLIC -lmingw32) # -mwindows
    add_definitions(-DSDL_MAIN_HANDLED)
endif()

### MinGW ###
target_link_options(${PROJECT_NAME} PUBLIC -static-libgcc -static-libstdc++)