#include "ThreadPool.h"
#include<Windows.h>
#include <iostream>
#include <exception>
#include "Logger.h"



int TestFunc1()
{
	for (int i = 0; i < 5; ++i)
	{
		printf("TestFunc1\n");
		fflush(stdout);
		Sleep(1000);
	}
	return 0;
}

int TestFunc2(const int intValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc2, parameters: %d\n", intValue);
		fflush(stdout);
		Sleep(1000);
	}
	return 0;
}

char TestFunc3(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc3, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
char TestFunc5(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc5, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
char TestFunc6(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc6, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
int TestFunc4(const int intValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc4, parameters: %d\n", intValue);
		fflush(stdout);
		Sleep(1000);
		if (i == 2)
			throw MyException();
	}
	return 0;
}

int main()
{
	int (*TestFunc11)() = TestFunc1;
	ThreadPoolInit(4,TestFunc1, TestFunc2, TestFunc3, TestFunc4, TestFunc5, TestFunc6);
	getchar();

	return 0;
}