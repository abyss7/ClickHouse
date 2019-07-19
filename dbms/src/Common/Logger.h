#pragma once

#include <Poco/Logger.h>

#include <list>
#include <sstream>

namespace DB
{

class Logger
{
public:
    enum class Level
    {
        none = 0, /// Disable
        error,
        warning,
        information,
        debug,
        trace,
    };

    Logger(Poco::Logger * poco_log, Level level);
    Logger(const char * log_name, Level level);
    ~Logger();

    Logger(Logger &&) = default;
    Logger(const Logger &) = delete;
    Logger & operator= (const Logger &) = delete;

    template <class T>
    Logger & operator<< (const T & message)
    {
        ss << message;
        return *this;
    }

    template <class T>
    Logger & operator<< (const std::list<T> & list)
    {
        auto it = list.begin();
        this->operator<<(*it);
        ++it;
        for (; it != list.end(); ++it)
        {
            ss << ", ";
            this->operator<<(*it);
        }

        return *this;
    }

    Logger & operator<< (std::ostream & (*fn)(std::ostream &)); // support |std::endl|

private:
    Poco::Logger * const log;
    const Level level;
    std::stringstream ss;
};

class WithLogger
{
public:
    WithLogger(const char * name) : logger(&Poco::Logger::get(name)) {}
    auto * getLogger() const { return logger; }

private:
    Poco::Logger * logger;
};

#define LOG(level) DB::Logger(getLogger(), DB::Logger::Level::level)
#if defined(NDEBUG)
#   define DLOG(logger, level) std::stringstream()
#else
#   define DLOG(logger, level) LOG(logger, level)
#endif

} // namespace DB
