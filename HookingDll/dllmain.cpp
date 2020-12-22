#include "pch.h"
#include <string>
#include <sstream>
#include "detours.h"


HANDLE hConsole;

template <typename T>
std::wstring ConvertToString(T value);
std::wstring GetFileName(HANDLE hFile);
std::wstring GetKeyPath(HKEY key);


LSTATUS(WINAPI* PRegCreateKey) (HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult) = RegCreateKey;
LSTATUS(WINAPI* PRegOpenKey) (HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult) = RegOpenKey;
LSTATUS(WINAPI* PRegGetValue) (HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData) = RegGetValue;
LSTATUS(WINAPI* PRegCloseKey) (HKEY hKey) = RegCloseKey;
LSTATUS(WINAPI* PRegSetValue) (HKEY hKey, LPCWSTR lpSubKey, DWORD dwType, LPCWSTR lpData, DWORD cbData) = RegSetValue;
HANDLE(WINAPI* PCreateFile) (LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFile;
HFILE(WINAPI* POpenFile) (LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle) = OpenFile;
LSTATUS(WINAPI* PRegDeleteKey) (HKEY hKey, LPCWSTR lpSubKey) = RegDeleteKey;
BOOL(WINAPI* PReadFile) (HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) = ReadFile;
BOOL(WINAPI* PWriteFile) (HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) = WriteFile;
BOOL(WINAPI* PDeleteFile) (LPCWSTR lpFileName) = DeleteFile;


LSTATUS WINAPI BreakingRegCreateKey(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    std::wstring message = L"Create key " + ConvertToString(lpSubKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegCreateKey(hKey, lpSubKey, phkResult);
}

LSTATUS WINAPI BreakingRegOpenKey(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    std::wstring message = L"Open key " + ConvertToString(lpSubKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegOpenKey(hKey, lpSubKey, phkResult);
}

LSTATUS WINAPI BreakingRegGetValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{
    std::wstring message = L"Get value from key" + GetKeyPath(hKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegGetValue(hKey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
}

LSTATUS WINAPI BreakingRegSetValue(HKEY hKey, LPCWSTR lpSubKey, DWORD dwType, LPCWSTR lpData, DWORD cbData)
{
    std::wstring message = L"Set value " + ConvertToString(lpData) + L" to key " + GetKeyPath(hKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegSetValue(hKey, lpSubKey, dwType, lpData, cbData);
}

LSTATUS WINAPI BreakingRegCloseKey(HKEY hKey)
{
    std::wstring message = L"Close key " + GetKeyPath(hKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegCloseKey(hKey);
}

LSTATUS WINAPI BreakingRegDeleteKey(HKEY hKey, LPCWSTR lpSubKey)
{
    std::wstring message = L"Delete key" + GetKeyPath(hKey) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PRegDeleteKey(hKey, lpSubKey);
}


HANDLE WINAPI BreakingCreateFile(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    std::wstring message = L"Create file: " + ConvertToString(lpFileName)+L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PCreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}


HFILE WINAPI BreakingOpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle)
{
    std::wstring message = L"Open file: " + ConvertToString(lpFileName) + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return POpenFile(lpFileName, lpReOpenBuff, uStyle);
}


BOOL WINAPI BreakingReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    std::wstring message = L"Read from file(" + GetFileName(hFile) + L") " + ConvertToString(nNumberOfBytesToRead) + L" bytes" + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL WINAPI BreakingWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    std::wstring message = L"Write to file(" + GetFileName(hFile) + L") " + ConvertToString(nNumberOfBytesToWrite) + L" bytes" + L"\n";
    WriteConsole(hConsole, message.c_str(), message.size(), NULL, NULL);
    return PWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

BOOL WINAPI BreakingDeleteFile(LPCWSTR lpFileName)
{
    std::wstring message = L"Delete file: " + ConvertToString(lpFileName) + L"\n";
    WriteConsole(hConsole, (message += L'\n').c_str(), message.size(), NULL, NULL);
    return PDeleteFile(lpFileName);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)PCreateFile, BreakingCreateFile);
        DetourAttach(&(PVOID&)POpenFile, BreakingOpenFile);
        DetourAttach(&(PVOID&)PReadFile, BreakingReadFile);
        DetourAttach(&(PVOID&)PWriteFile, BreakingWriteFile);
        DetourAttach(&(PVOID&)PDeleteFile, BreakingDeleteFile);
        DetourAttach(&(PVOID&)PRegCreateKey, BreakingRegCreateKey);
        DetourAttach(&(PVOID&)PRegOpenKey, BreakingRegOpenKey);
        DetourAttach(&(PVOID&)PRegGetValue, BreakingRegGetValue);
        DetourAttach(&(PVOID&)PRegSetValue, BreakingRegSetValue);
        DetourAttach(&(PVOID&)PRegCloseKey, BreakingRegCloseKey);
        DetourAttach(&(PVOID&)PRegDeleteKey, BreakingRegDeleteKey);
        DetourTransactionCommit();
        break;

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)PCreateFile, BreakingCreateFile);
        DetourDetach(&(PVOID&)POpenFile, BreakingOpenFile);
        DetourDetach(&(PVOID&)PReadFile, BreakingReadFile);
        DetourDetach(&(PVOID&)PWriteFile, BreakingWriteFile);
        DetourDetach(&(PVOID&)PDeleteFile, BreakingDeleteFile);
        DetourDetach(&(PVOID&)PRegCreateKey, BreakingRegCreateKey);
        DetourDetach(&(PVOID&)PRegOpenKey, BreakingRegOpenKey);
        DetourDetach(&(PVOID&)PRegGetValue, BreakingRegGetValue);
        DetourDetach(&(PVOID&)PRegSetValue, BreakingRegSetValue);
        DetourDetach(&(PVOID&)PRegCloseKey, BreakingRegCloseKey);
        DetourDetach(&(PVOID&)PRegDeleteKey, BreakingRegDeleteKey);
        DetourTransactionCommit();
        CloseHandle(hConsole);
        break;
    }
    return TRUE;
}

template <typename T>
std::wstring ConvertToString(T value)
{
    std::wostringstream wss;
    wss << value;
    return wss.str();
}

std::wstring GetFileName(HANDLE hFile)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)PCreateFile, BreakingCreateFile);
    DetourTransactionCommit();

    WCHAR buffer[MAX_PATH];
    GetFinalPathNameByHandle(hFile, buffer, MAX_PATH, FILE_NAME_NORMALIZED);


    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)PCreateFile, BreakingCreateFile);
    DetourTransactionCommit();

    std::wstring filePath = buffer;
    size_t i = filePath.rfind('\\', filePath.length());
    if (i != std::wstring::npos) {
        return(filePath.substr(i + 1, filePath.length() - i));
    }
    return L"Console";
}

std::wstring GetKeyPath(HKEY key)
{
    std::wstring keyPath;
    if (key != NULL)
    {
        HMODULE dll = LoadLibrary(L"ntdll.dll");
        if (dll != NULL) {
            typedef DWORD(__stdcall* NtQueryKeyType) (HANDLE  KeyHandle, int KeyInformationClass, PVOID  KeyInformation, ULONG  Length, PULONG  ResultLength);

            NtQueryKeyType ntQueryKeyAddress = reinterpret_cast<NtQueryKeyType>(::GetProcAddress(dll, "NtQueryKey"));

            if (ntQueryKeyAddress != NULL) {
                DWORD size = 0;
                DWORD result = 0;
                result = ntQueryKeyAddress(key, 3, 0, 0, &size);
                if (result == (LONG)0xC0000023L)
                {
                    size = size + 2;
                    wchar_t* buffer = new (std::nothrow) wchar_t[size / sizeof(wchar_t)];
                    if (buffer != NULL)
                    {
                        result = ntQueryKeyAddress(key, 3, buffer, size, &size);
                        if (result == (LONG)0x00000000L)
                        {
                            buffer[size / sizeof(wchar_t)] = L'\0';
                            keyPath = std::wstring(buffer + 2);
                        }

                        delete[] buffer;
                    }
                }
            }

            FreeLibrary(dll);
        }
    }
    return keyPath;
}


