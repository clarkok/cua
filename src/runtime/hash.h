#ifndef _CUA_HASH_H_
#define _CUA_HASH_H_

#include <string>
#include <functional>

#include "../config.h"

namespace CUA {
    typedef std::function<Config::T_OID(std::string)> Hasher;
    
    Hasher &getDefaultHasher();
}

#endif // _CUA_HASH_H_