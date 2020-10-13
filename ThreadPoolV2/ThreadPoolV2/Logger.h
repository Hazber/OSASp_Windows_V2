#pragma once
#include<Windows.h>
#include <chrono>
#include <ctime> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Logger {
public:

	void LogInit(int count) {
		outstr.open("Logss.txt");
		std::ostringstream oss;
		oss << count;
		std::string s = oss.str();
		if (outstr.is_open())
		{
			outstr << "ThreadPool with " + s + " threads is successfully created!" << std::endl;
		}
	}

	void LogFileWrite(int num,int flag)
	{
		std::ostringstream oss;
		oss << num;
		std::string s = oss.str();
		if (outstr.is_open())
		{
			switch (flag)
			{
				case 1:
				{
					outstr << "Task " + s + " successfully added to ThreadPool Task que" << std::endl;
				}
				break;
				case 2:
				{
					outstr << "Error adding Task" + s << std::endl;
				}
				break;
				case 3:
				{
					outstr << "Exception on Task" + s << std::endl;
				}
			}
		}

	}
	
	void StopLog() {
		outstr.close();
	}
	
private:
	std::ofstream outstr;
	

};