#include <Common/Logger.h>

#include <Common/CurrentThread.h>

#include <Poco/Logger.h>

namespace DB
{

namespace
{

std::unordered_map<Logger::Level, Poco::Message::Priority> priority_map =
{
    {Logger::Level::error, Poco::Message::PRIO_ERROR},
    {Logger::Level::warning, Poco::Message::PRIO_WARNING},
    {Logger::Level::information, Poco::Message::PRIO_INFORMATION},
    {Logger::Level::debug, Poco::Message::PRIO_DEBUG},
    {Logger::Level::trace, Poco::Message::PRIO_TRACE},
};

}

Logger::Logger(Poco::Logger * log_, Logger::Level level_) : log(log_), level(level_)
{
}

Logger::Logger(const char * log_name, Logger::Level level_) : log(&Poco::Logger::get(log_name), level_)
{
}

Logger::~Logger()
{
    const bool is_clients_log = (CurrentThread::getGroup() != nullptr) && (CurrentThread::getGroup()->client_logs_level >= level);

    if (log->is(priority_map[level]) || is_clients_log)
        if (auto channel = log->getChannel())
        {
            ss << std::endl;
            channel->log(Poco::Message(log->name(), ss.str(), priority_map[level]));
        }
}

Logger & Logger::operator<< (std::ostream & (*fn)(std::ostream &))
{
    ss << fn;
    return *this;
}

} // namespace DB
