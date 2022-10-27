//
// Created by Benjam on 10/27/2022.
//

#ifndef TREMA_LIB_TREMAPROGRAM_H
#define TREMA_LIB_TREMAPROGRAM_H

#include <vector>
#include <string>

extern int Main(const std::vector<std::string>& args);

#ifdef WIN32
    #include <Windows.h>

    LPSTR* CommandLineToArgvA(LPSTR lpCmdLine, INT *pNumArgs)
    {
        int retval;
        retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, NULL, 0);
        if (!SUCCEEDED(retval))
            return NULL;

        LPWSTR lpWideCharStr = (LPWSTR)malloc(retval * sizeof(WCHAR));
        if (lpWideCharStr == NULL)
            return NULL;

        retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, lpWideCharStr, retval);
        if (!SUCCEEDED(retval))
        {
            free(lpWideCharStr);
            return NULL;
        }

        int numArgs;
        LPWSTR* args;
        args = CommandLineToArgvW(lpWideCharStr, &numArgs);
        free(lpWideCharStr);
        if (args == NULL)
            return NULL;

        int storage = numArgs * sizeof(LPSTR);
        for (int i = 0; i < numArgs; ++ i)
        {
            BOOL lpUsedDefaultChar = FALSE;
            retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, NULL, 0, NULL, &lpUsedDefaultChar);
            if (!SUCCEEDED(retval))
            {
                LocalFree(args);
                return NULL;
            }

            storage += retval;
        }

        LPSTR* result = (LPSTR*)LocalAlloc(LMEM_FIXED, storage);
        if (result == NULL)
        {
            LocalFree(args);
            return NULL;
        }

        int bufLen = storage - numArgs * sizeof(LPSTR);
        LPSTR buffer = ((LPSTR)result) + numArgs * sizeof(LPSTR);
        for (int i = 0; i < numArgs; ++ i)
        {
            BOOL lpUsedDefaultChar = FALSE;
            retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, buffer, bufLen, NULL, &lpUsedDefaultChar);
            if (!SUCCEEDED(retval))
            {
                LocalFree(result);
                LocalFree(args);
                return NULL;
            }

            result[i] = buffer;
            buffer += retval;
            bufLen -= retval;
        }

        LocalFree(args);

        *pNumArgs = numArgs;
        return result;
    }

    #define TremaMain() int CALLBACK WinMain(                           \
            HINSTANCE hInstance, HINSTANCE hPrevInstance,               \
            LPSTR lpCmdLine, int nCmdShow                               \
        )                                                               \
    {                                                                   \
        int argc;                                                       \
        LPSTR* argv = CommandLineToArgvA(GetCommandLine(), &argc);      \
        std::vector<std::string> args;                                  \
        for (int i = 0; i < argc; i++)                                  \
            args.emplace_back(std::string(argv[i]));                    \
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
