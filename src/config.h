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
        
        static const char LENGTH_KEY[] = "length";
    }
}

#endif // _CUA_CONFIG_H_