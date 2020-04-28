#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <thread>

_declspec(dllimport) void Hook();
#pragma comment(lib, "HookDll.lib")

int main()
{
    Hook();
    MSG msg;
    // 控制台程序要自行添加消息处理
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE) != 0)
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    return 0;
}
