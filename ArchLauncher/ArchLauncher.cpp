#include "stdafx.h"

EXTERN_C { 
 DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, LPDWORD lpThreadId, 
       VOID* apiThreadStartup, LPTHREAD_START_ROUTINE lpStartAddress, 
       LPVOID lpParameter, DWORD dwCreationFlagsMod);
 VOID  XapiThreadStartup(VOID (__cdecl *StartRoutine)(VOID*), VOID* StartContext);
 DWORD XexLoadImage(CHAR* ImagePath, DWORD LoadFlags, DWORD Version, HMODULE* ModuleHandle);
}

DWORD loadStatus = -1;

VOID LaunchPlugin() {
 loadStatus = XexLoadImage("GAME:\\ArchEngine.xex", 8, 0, NULL);

}

void __cdecl main() {

 // Create a system thread to launch our "system plugin"
 HANDLE hThread; DWORD threadId;
 ExCreateThread(&hThread, 0, &threadId, (VOID*)XapiThreadStartup, 
  (LPTHREAD_START_ROUTINE)LaunchPlugin, NULL, 0x2);

 // Gotta do this because it wont start on its own for some reason >_<
 XSetThreadProcessor(hThread, 4);
 SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
 ResumeThread(hThread);

 // Loop as long as we havent loaded it yet or didnt get a error
 while(loadStatus == -1) {
  Sleep(0);
    }

	XLaunchNewImage("GAME:\\ArchHalo4.xex", NULL);
}