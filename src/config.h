#ifndef _CUA_CONFIG_H_
#define _CUA_CONFIG_H_

#include <cstdint>

namespace CUA {
    
    namespace Config {
        static const char VERSION[] = "0.0.1";
        static const int VERSION_NUMBER = 000001;
        
        typedef std::uint64_t T_OID;
        static const T_OID INVALID_ID = (0ull - 1);
        
        static const char CHILD_SCOPE_KEY[] = "__child_scopes__";
        static const char UPPER_SCOPE_KEY[] = "__upper_scope__";
        
        static const char LENGTH_KEY[] = "length";
        
        static const char SCOPE_LOCAL_PREFIX[] = "@";
        static const char SCOPE_COMPILE_TEMP_PREFIX[] = "#";
        static const char SCOPE_LITERAL_PREFIX[] = "~";
        static const char SCOPE_TEMP_LABEL_PREFIX[] = "#";
    }
}

#endif // _CUA_CONFIG_H_