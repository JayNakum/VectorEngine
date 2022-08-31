#pragma once

#include <iostream>
#include <chrono>

class Log {

    static Log* instance;

    Log() {}

public:
    static Log* getLogger() {
        if (!instance)
            instance = new Log();
        return instance;
    }
    enum Level : unsigned char
    {
        LevelTrace = 0,
        LevelInfo,
        LevelWarning,
        LevelError,
        LevelCritical
    };

    void setLevel(Level level)
    {
        m_logLevel = level;
    }

    void trace(std::string message)
    {
        if (m_logLevel <= LevelTrace)
        {
            m_time = time(NULL);
            localtime_s(&now, &m_time);
            std::cout << "\x1B[37m"
                << "[" << (now.tm_hour) << ":" << (now.tm_min) << ":" << (now.tm_sec) << "] "
                << message
                << "\x1B[00m"
                << std::endl;
        }
    }

    void info(std::string message)
    {
        if (m_logLevel <= LevelInfo)
        {
            m_time = time(NULL);
            localtime_s(&now, &m_time);
            std::cout << "\x1B[32m"
                << "[" << (now.tm_hour) << ":" << (now.tm_min) << ":" << (now.tm_sec) << "] "
                << message
                << "\x1B[00m"
                << std::endl;
        }
    }

    void warning(std::string message)
    {
        if (m_logLevel <= LevelWarning)
        {
            m_time = time(NULL);
            localtime_s(&now, &m_time);
            std::cout << "\x1B[33m"
                << "[" << (now.tm_hour) << ":" << (now.tm_min) << ":" << (now.tm_sec) << "] "
                << message
                << "\x1B[00m"
                << std::endl;
        }
    }

    void error(std::string message)
    {
        if (m_logLevel <= LevelError)
        {
            m_time = time(NULL);
            localtime_s(&now, &m_time);
            std::cout << "\x1B[31m"
                << "[" << (now.tm_hour) << ":" << (now.tm_min) << ":" << (now.tm_sec) << "] "
                << message
                << "\x1B[00m"
                << std::endl;
        }
    }

    void critical(std::string message)
    {
        if (m_logLevel <= LevelCritical)
        {
            m_time = time(NULL);
            localtime_s(&now, &m_time);
            std::cout << "\x1B[43m\x1B[30m"
                << "[" << (now.tm_hour) << ":" << (now.tm_min) << ":" << (now.tm_sec) << "] "
                << message
                << "\x1B[00m"
                << std::endl;
        }
    }

private:
    Level m_logLevel = LevelTrace;
    time_t m_time = time(NULL);
    struct tm now = {};
};

#define TRACE(message) Log::getLogger()->trace(message)
#define INFO(message) Log::getLogger()->info(message)
#define WARN(message) Log::getLogger()->warning(message)
#define ERROR(message) Log::getLogger()->error(message)
#define CRITICAL(message) Log::getLogger()->critical(message)