#ifndef _CUA_EXCEPTION_H_
#define _CUA_EXCEPTION_H_

#include <string>
#include <cstdio>
#include <cstdarg>

namespace CUA {
    struct Exception
    {
        std::string major_msg;
        std::string minor_msg;
        
        Exception(std::string major_msg, std::string minor_msg = "")
        : major_msg(major_msg), minor_msg(minor_msg)
        { }
        
        inline int
        printf(const char *format, ...)
        {
            char buffer[256];
            va_list args;
            va_start(args, format);
            auto ret = std::vsprintf(buffer, format, args);
            va_end(args);
            
            minor_msg += buffer;
            return ret;
        }
        
        inline std::string
        toString() const
        { return major_msg + ' ' + minor_msg; }
    };
};

#endif // _CUA_EXCEPTION_H_