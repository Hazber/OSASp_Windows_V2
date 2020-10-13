#include "ThreadPool.h"
#include "Logger.h"

ThreadPool::ThreadPool(int threadCount)
{
    mThreadCount = threadCount;
    mThreads = new HANDLE[mThreadCount];
    InitializeCriticalSection(&mCriticalSection);
    InitializeConditionVariable(&mConditionVariable);
    InitializeConditionVariable(&mConditionVariableTaskFinished);
    mConsum = true;
	logger->LogInit(threadCount);
    for (int i = 0; i < mThreadCount; i++)
        mThreads[i] = CreateThread(NULL, 0, ThreadStart, (void*)this, 0, NULL);
}

DWORD WINAPI ThreadPool::ThreadStart(LPVOID threadParameters) 
{
    ThreadPool* referenceToThis = (ThreadPool*)threadParameters;
    return referenceToThis->ThreadMain();
}

DWORD ThreadPool::ThreadMain() 
{
    do
    {
        Task currentTask;
        EnterCriticalSection(&mCriticalSection);

        while (mTasks.size() == 0 && mConsum)
            SleepConditionVariableCS(&mConditionVariable, &mCriticalSection, INFINITE);

        if (!mConsum)
        {
            LeaveCriticalSection(&mCriticalSection);
            return 0;
        }
        currentTask = mTasks.front();
        mTasks.pop_front();

        LeaveCriticalSection(&mCriticalSection);
        currentTask();
        WakeConditionVariable(&mConditionVariableTaskFinished);
    } while (mConsum);

    return 0;
}

ThreadPool::~ThreadPool()
{
    mConsum = false;
    WakeAllConditionVariable(&mConditionVariable);
    WaitForMultipleObjects(mThreadCount, mThreads, true, INFINITE);
    DeleteCriticalSection(&mCriticalSection);
}

VOID ThreadPoolWork(int numofThreads,int (*TestFunc1)(), int (*TestFunc2)(int), int (*TestFunc3)(int), int (*TestFunc4)(int), char (*TestFunc5)(int,string), bool (*TestFunc6)(int,string))
{
	ThreadPool* pool = new ThreadPool(numofThreads);
	auto result_1 = pool->addTask(TestFunc1);
	auto result_2 = pool->addTask(TestFunc2, 42);
	auto result_3 = pool->addTask(TestFunc3, 22);
	auto result_4 = pool->addTask(TestFunc4, 22);
	auto result_5 = pool->addTask(TestFunc5, 22, std::string("Task5"));
	auto result_6 = pool->addTask(TestFunc6, 22, std::string("Task6"));

	try {
		printf("TestFunc1 result = %d\n", result_1.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(1,3);
	}
	catch (std::exception& e) {
		std::cout << "Task 1 was declined" << std::endl;
		pool->logger->LogFileWrite(1,3);
	}

	try {
		printf("TestFunc2 result = %d\n", result_2.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(2,3);
	}
	catch (std::exception& e) {
		std::cout << "Task 2 was declined" << std::endl;
	}

	try {
		printf("TestFunc3 result = %d\n", result_3.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(3,3);
	}
	catch (std::exception& e) {
		std::cout << "Task 3 was declined" << std::endl;
	}

	try
	{
		printf("TestFunc4 result = %d\n", result_4.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(4,3);
	}
	catch (std::exception& e) {
		std::cout << "Task 4 was declined" << std::endl;
	}
	
	try
	{
		printf("TestFunc5 result = %d\n", result_5.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(5,3);
	}
	catch (std::exception& e) {
		std::cout << "Task 5 was declined" << std::endl;
	}

	try {
		printf("TestFunc6 result = %d\n", result_6.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->logger->LogFileWrite(6, 3);
	}
	catch (std::exception& e) {
		std::cout << "Task 6 was declined" << std::endl;
	}

	pool->logger->StopLog();
}