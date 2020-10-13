#pragma once
#include<time.h>
#include <Windows.h>
#include<list>
#include<functional>
#include <future>
#include <iostream>
#include "Logger.h"
using namespace std;



VOID ThreadPoolWork(int numofThreads, int (*TestFunc1)(), int (*TestFunc2)(int), int (*TestFunc3)(int), int (*TestFunc4)(int), char (*TestFunc5)(int, string), bool (*TestFunc6)(int, string));
struct MyException : public std::exception
{
    const char* what() const throw ()
    {
        return "Task Exception";
    }
};
class ThreadPool
{
public:  
    using Task = std::function<void()>;
    ThreadPool(int threadCount = 0);
    Logger* logger = new Logger();

    template<class Func, class... Args>
    auto addTask(Func&& func, Args&&...args) ->std::future<typename std::result_of<Func(Args...)>::type>
    {
        
        using returnType = typename std::result_of<Func(Args...)>::type;
        auto wrapper = std::make_shared< std::packaged_task<returnType()> >([func, args...]() { return func(args...); });
        if (mNumberOfTasksNotFinished == mThreadCount) overFlow = true;
        if (!overFlow)
        {
            EnterCriticalSection(&mCriticalSection);
            mTasks.push_back([=] {(*wrapper)(); });
            mNumberOfTasksNotFinished++;
            LeaveCriticalSection(&mCriticalSection);
            WakeConditionVariable(&mConditionVariable);
            logger->LogFileWrite(mNumberOfTasksNotFinished,1);
            return wrapper->get_future();
           
        }
        else {
            printf("All threads are working\n");
            logger->LogFileWrite(mNumberOfTasksNotFinished, 2);
            return wrapper->get_future();
        }
        
    }

  

    ~ThreadPool();

private:
    static DWORD WINAPI ThreadStart(LPVOID threadParameters);
    DWORD ThreadMain();
    CRITICAL_SECTION mCriticalSection;
    CONDITION_VARIABLE mConditionVariable;
    CONDITION_VARIABLE mConditionVariableTaskFinished;
    int mNumberOfTasksNotFinished;
    list<Task> mTasks;
    HANDLE* mThreads;
    int mThreadCount;
    bool mConsum;
    bool overFlow = false;
};