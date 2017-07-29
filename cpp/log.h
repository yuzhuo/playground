
#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>


enum LogLevel {
    kDebug,
    kInfo,
    kWarning,
    kError,
    kCritical,
    kOff,
};

#if __cplusplus >= 201103L
#define __FUNCTION__ __func__
#elif !defined(__FUNCTION__)
#define __FUNCTION__ "macro __FUNCTION__ not supported!"
#endif


#ifdef NDEBUG

#define LOG_OFF
#define LOG_SET_LEVEL(lvl)
#define LOG_SET_FILE(file)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)
#define LOG_METHOD()
#define LOG_METHOD_INFO()
#define LOG(lvl, msg)

#else

#define LOG_OFF() do { Logger::instance().set_level("off"); } while(0)
#define LOG_SET_LEVEL(lvl) do { Logger::instance().set_level(lvl); } while(0)
#define LOG_SET_FILE(file) do { Logger::instance().set_log_file(file); } while(0)
#define LOG_DEBUG(...) LOG(kDebug, __VA_ARGS__)
#define LOG_INFO(...) LOG(kInfo, __VA_ARGS__)
#define LOG_WARNING(...) LOG(kWarning, __VA_ARGS__)
#define LOG_ERROR(...) LOG(kError, __VA_ARGS__)
#define LOG_CRITICAL(...) LOG(kCritical, __VA_ARGS__)
#define LOG_METHOD() LOG(kDebug, __FUNCTION__)
#define LOG_METHOD_INFO() LOG(kInfo, __FUNCTION__)
#define LOG(lvl, ...) \
    do { \
        assert(lvl >= kDebug && lvl <= kCritical); \
        if (lvl >= Logger::instance().level()) { \
            Logger::instance().log(__FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while(0)

#endif

class Logger
{
public:
    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    ~Logger()
    {
        os_->flush();
    }

    void set_log_file(char* file_name)
    {
        assert(!set_);
        static std::ofstream ofs(file_name);
        os_ = &ofs;

        set_ = true;
    }


    LogLevel level()
    {
        return level_;
    }

    void set_level(const char* level)
    {
        if (kOff == level_)
            return;

        if (!strcmp(level, "debug"))
            level_ = kDebug;
        else if (!strcmp(level, "info"))
            level_ = kInfo;
        else if (!strcmp(level, "warning"))
            level_ = kWarning;
        else if (!strcmp(level, "error"))
            level_ = kError;
        else if (!strcmp(level, "critical"))
            level_ = kCritical;
        else if (!strcmp(level, "off"))
            level_ = kOff;
        else
            assert(!"level is not one of [debug, info, warning, error, critical]");
    }

    void log(const char* file, int line, const char* format) // base function
    {
        if (nullptr != file)
            *os_ << file << ":" << line << " ";

        *os_ << format << std::endl;
    }

    template<typename T, typename... Targs>
    void log(const char* file, int line, const char* format, T value, Targs... Fargs) // recursive variadic function
    {
        if (nullptr != file)
            *os_ << file << ":" << line << " ";

        for ( ; *format != '\0'; format++  ) {
            if ( *format == '%'  ) {
                *os_ << value;
                log(nullptr, 0, format+1, Fargs...); // recursive call
                return;

            }
            *os_ << *format;
        }
    }

private:
    Logger()
        : os_(&std::cout)
        , set_(false)
        , level_(kInfo)
    {
    }

private:
    std::ostream* os_;
    bool set_;
    LogLevel level_;
};

#endif /* __LOG_H__ */

