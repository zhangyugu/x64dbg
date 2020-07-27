/**
 @file x64dbg_exe.cpp

 @brief Implements the 64 debug executable class.
 */

#include <stdio.h>
#include <windows.h>
#include "crashdump.h"
#include "../bridge/bridgemain.h"
#include "LoadResourceString.h"

/**
 @fn int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)

 @brief Window main.

 @param hInstance     The instance.
 @param hPrevInstance The previous instance.
 @param lpCmdLine     The command line.
 @param nShowCmd      The show command.

 @return An APIENTRY.
 */
typedef int (FAR WINAPI *FUN)(int, int);
typedef void (FAR WINAPI *MESSAGEBOX)();
int sum = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    CrashDumpInitialize();
    
    DWORD error;
    //HMODULE hInst=LoadLibraryW(L"D:\\QtCode\\build-Library-Desktop_Qt_5_14_1_MSVC2017_32bit-Release\\release\\Library.dll");
    HMODULE hInst = LoadLibraryW(L"x32gui.dll");
    if(!hInst) 
    {
        error = GetLastError(); 
        return error;
    }
    else
    {
        FUN fun = (FUN)GetProcAddress(hInst, "add");
        if (fun)
            sum = fun(5, 5);
        MESSAGEBOX _MessageBox = (MESSAGEBOX)GetProcAddress(hInst, "MessageBox");
        if (_MessageBox)
            _MessageBox();
    }
    
    const wchar_t* errormsg = BridgeInit();
    if(errormsg)
    {
        MessageBoxW(0, errormsg, LoadResString(IDS_BRIDGEINITERR), MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }
    errormsg = BridgeStart();
    if(errormsg)
    {
        MessageBoxW(0, errormsg, LoadResString(IDS_BRIDGESTARTERR), MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }
   
    return 0;
}
