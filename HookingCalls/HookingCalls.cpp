#include <iostream>
#include <windows.h>

STARTUPINFO stratupInfo;
PROCESS_INFORMATION processInformation;

int main()
{
    std::wstring path = L"D:\\ОСиСП\\HookingLab\\x64\\Debug\\TestApp.exe";
    std::wstring dll = L"D:\\ОСиСП\\HookingLab\\x64\\Debug\\HookingDll.dll";

    CreateProcess(path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &stratupInfo, &processInformation);

    void* loadLibraryW = GetProcAddress(GetModuleHandle(L"Kernel32"), "LoadLibraryW");
    LPVOID hMem = VirtualAllocEx(processInformation.hProcess, NULL, dll.size() * sizeof(wchar_t) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(processInformation.hProcess, hMem, dll.c_str(), dll.size() * sizeof(wchar_t) + 1, NULL);

    HANDLE hRemoteThread = CreateRemoteThread(processInformation.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryW, hMem, NULL, NULL);
    WaitForSingleObject(hRemoteThread, INFINITE);
    CloseHandle(hRemoteThread);

    ResumeThread(processInformation.hThread);
    WaitForSingleObject(processInformation.hProcess, INFINITE);

    VirtualFreeEx(processInformation.hProcess, hMem, 0, MEM_RELEASE);
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);
}
