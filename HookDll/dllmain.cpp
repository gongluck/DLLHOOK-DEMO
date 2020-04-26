// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

HHOOK g_hmouse = nullptr;
HHOOK g_hkey = nullptr;

LRESULT CALLBACK MouseProc(
    int nCode,      // hook code
    WPARAM wParam,  // message identifier
    LPARAM lParam   // mouse coordinates
)
{
    return 1;
}
LRESULT CALLBACK KeyboardProc(
    int code,       // hook code
    WPARAM wParam,  // virtual-key code
    LPARAM lParam   // keystroke-message information
)
{
    if (VK_F2 == wParam)
    {
        UnhookWindowsHookEx(g_hmouse);
        UnhookWindowsHookEx(g_hkey);
        MessageBeep(-1);
    }
    return 1;
}

void Hook()
{
    g_hmouse = SetWindowsHookEx(WH_MOUSE, MouseProc, GetModuleHandle(TEXT("HookDll")), 0);
    g_hkey = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle(TEXT("HookDll")), 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

