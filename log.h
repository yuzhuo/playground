
#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <fstream>
#include <cassert>

#if __cplusplus >= 201103L
#define __FUNCTION__ __func__
#elif !defined(__FUNCTION__)
#define __FUNCTION__ "__FUNCTION__ not supported!"
#endif


#ifdef NDEBUG

#define LOG_SET_FILE(file)
#define LOG(msg)
#define LOG_METHOD()

#else

#define LOG_SET_FILE(file) do { Logger::instance().set_log_file(file); } while(0)
#define LOG(...) do { Logger::instance().log(__FILE__, __LINE__, __VA_ARGS__); } while(0)
#define LOG_METHOD() do { Logger::instance().log(__FILE__, __LINE__, __FUNCTION__); } while(0)

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
    {
    }

private:
    std::ostream* os_;
    bool set_;
};

#endif /* __LOG_H__ */

