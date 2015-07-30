#pragma once

/*
** Source: http://stackoverflow.com/questions/6168107/how-to-implement-a-good-debug-logging-feature-in-a-project
*/

#include <iostream>
#include <sstream>


enum LogLevel
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG
};


static LogLevel logLevel;


class Log
{
public:
    Log();
    ~Log();
	
public:
	template <typename T>
    Log & operator<<(T const & value)
    {
		if (logLevel <= reportingLevel)
		{
	        //buffer << value << std::endl;
	        //std::cerr << buffer.str();
	        std::cerr << value << std::endl;
		}
        return *this;
    }

public:
	LogLevel reportingLevel;
	
private:
    std::ostringstream	buffer;
};


static Log outLog;

