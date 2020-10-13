#include "ThreadPool.h"
#include<Windows.h>
#include <iostream>
#include <exception>




int TestFunc1()
{
	printf("TestFunc1\n");
	fflush(stdout);
	Sleep(1000);
	return 0;
}

int TestFunc2(const int intValue)
{
	printf("ThreadFunc2, parameters: %d\n", intValue);
	fflush(stdout);
	Sleep(1000);
	return 0;
}

int TestFunc3(const int intValue)
{
	printf("ThreadFunc3, parameters: %d\n", intValue);
	fflush(stdout);
	Sleep(1000);
	return 'a';
}
int TestFunc4(const int intValue)
{
	printf("ThreadFunc4, parameters: %d\n", intValue);
	fflush(stdout);
	Sleep(1000);
	if (intValue == 42)
		throw MyException();
	return 0;
}
char TestFunc5(const int intValue, const std::string stringValue)
{
	printf("ThreadFunc5, parameters: %d %s\n", intValue, stringValue.c_str());
	fflush(stdout);
	Sleep(1000);
	return 'a';
}
bool TestFunc6(const int intValue, const std::string stringValue)
{
	printf("ThreadFunc6, parameters: %d %s\n", intValue, stringValue.c_str());
	fflush(stdout);
	Sleep(1000);
	return FALSE ;
}

DWORD WINAPI DominantThread(LPVOID threadParameters)
{
	ThreadPoolWork(5, TestFunc1, TestFunc2, TestFunc3, TestFunc4, TestFunc5, TestFunc6);
	return 1;
}


int main()
{
	
	HANDLE* hDominantThread;
	hDominantThread = new HANDLE[0];
	hDominantThread[0]=CreateThread(NULL,0,DominantThread,NULL,0,NULL);
	getchar();

	return 0;
}