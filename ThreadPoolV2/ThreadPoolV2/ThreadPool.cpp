#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadCount)
{
    mThreadCount = threadCount;
    mThreads = new HANDLE[mThreadCount];

    InitializeCriticalSection(&mCriticalSection);
    InitializeConditionVariable(&mConditionVariable);
    InitializeConditionVariable(&mConditionVariableTaskFinished);
    mConsum = true;
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

VOID ThreadPoolInit(int numofThreads,int (*TestFunc1)(), int (*TestFunc2)(int), char (*TestFunc3)(int,string), int (*TestFunc4)(int), char (*TestFunc5)(int,string), char (*TestFunc6)(int,string))
{
	ThreadPool* pool = new ThreadPool(numofThreads);
	
	auto res1 = pool->addTask(TestFunc1);
	auto res2 = pool->addTask(TestFunc2, 42);
	auto res3 = pool->addTask(TestFunc3, 22, std::string("Hello thread3"));
	auto res4 = pool->addTask(TestFunc4, 22);
	auto res5 = pool->addTask(TestFunc5, 22, std::string("Hello thread5"));
	auto res6 = pool->addTask(TestFunc6, 22, std::string("Hello thread6"));

	try {
		printf("TestFunc1 result = %d\n", res1.get());
		//pool->
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Task 1 was declined" << std::endl;
	}

	try {
		printf("TestFunc2 result = %d\n", res2.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Task 2 was declined" << std::endl;
	}

	try {
		printf("TestFunc3 result = %d\n", res3.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Task 3 was declined" << std::endl;
	}

	try {
		printf("TestFunc6 result = %d\n", res6.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Task 6 was declined" << std::endl;
	}

	try
	{
		printf("TestFunc4 result = %d\n", res4.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "Task 4 was declined" << std::endl;
	}

}