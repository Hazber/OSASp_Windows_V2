#pragma once
#include<Windows.h>
const TCHAR fileName[] = L"Logs.txt";
const TCHAR msgInit[] = L"Threadpool with %d pool was created %s.";

//DWORD ThreadPoolLoggerInit(int threadCount);
class Logger {
public:

	

	Logger()
	{
	     hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	/*DWORD ThreadPoolLoggerInit(HANDLE hFile,int threadCount)
	{
		DWORD dwTemp;
		WriteFile(hFile, &msgInit, sizeof(msgInit), &dwTemp, NULL);
	}

	DWORD LoggerTaskAdding(HANDLE hFile,int taskNum)
	{

	}*/
	DWORD LogFileWrite(TCHAR usingString[], int num_or_count)
	{
		DWORD dwTemp;
		WriteFile(hFile, &msgInit, sizeof(msgInit), &dwTemp, NULL);
	}

	DWORD StopLog()
	{
		CloseHandle(hFile);
	}
private:
	HANDLE hFile;
	
};