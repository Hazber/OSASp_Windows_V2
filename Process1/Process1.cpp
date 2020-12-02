﻿#include <iostream>
#include <Windows.h>

TCHAR szName[] = TEXT("MySharedMemory");

using namespace std;
int main()
{
    LPCRITICAL_SECTION critical_section;
    HANDLE hFileMapping;

    hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);

    if (hFileMapping == NULL)
    {
        cout << "Couldn't open FileMapping object" << endl;
        return 1;
    }

    critical_section = (LPCRITICAL_SECTION)MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CRITICAL_SECTION));

    if (critical_section == NULL)
    {
        cout << "Couldn't map view of file" << endl;
        CloseHandle(hFileMapping);
        return 1;
    }

    bool f = true;
    while (f)
    if (TryEnterCriticalSection(critical_section))
    {
        std::cout << 1 << std::endl;
        std::cout << 2 << std::endl;
        std::cout << 3 << std::endl;
        std::cout << 4 << std::endl;
        std::cout << 5 << std::endl;
        std::cout << 6 << std::endl;
        LeaveCriticalSection(critical_section);
        f = false;
    }

    UnmapViewOfFile(critical_section);

    CloseHandle(hFileMapping);

    return 0;
}
