//
// Created by Benjam on 10/27/2022.
//

#ifndef TREMA_LIB_TREMAPROGRAM_H
#define TREMA_LIB_TREMAPROGRAM_H

#include <vector>
#include <string>

extern int Main(const std::vector<std::string>& args);

#ifdef WIN32
    #include <windows.h>

    #define TremaMain() int CALLBACK WinMain(                           \
            HINSTANCE hInstance, HINSTANCE hPrevInstance,               \
            LPSTR lpCmdLine, int nCmdShow                               \
        )                                                               \
    {                                                                   \
        int argc;                                                       \
        LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);    \
        std::vector<std::string> args;                                  \
        for (int i = 0; i < argc; i++)                                  \
            args.push_back(std::string(argv[i]));                       \
        return Main(args);                                              \
    }

#else

    #define TremaMain() int main(int argc, char* argv[])                \
    {                                                                   \
        std::vector<std::string> args;                                  \
        for (int i = 0; i < argc; i ++)                                 \
            args.emplace_back(std::string(argv[i]));                    \
        return Main(args);                                              \
    }

#endif

TremaMain();

#endif //TREMA_LIB_TREMAPROGRAM_H
