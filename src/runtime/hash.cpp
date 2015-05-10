#include "hash.h"

using namespace CUA;

Hasher FNVHasher = [](std::string s) {
    Config::T_OID hash = 14695981039346656037ull;
    const char *limit = s.data() + s.length(),
               *p;
    for (
        p = s.data();
        p < limit - sizeof(Config::T_OID);
        p += sizeof(Config::T_OID)
    ) {
        hash *= 1099511628211ull;
        hash ^= *reinterpret_cast<const Config::T_OID*>(p);
    }
    p -= (sizeof(Config::T_OID) - 1);
    
    Config::T_OID last = 0;
    
    for (
        int count = 0;
        p < limit;
        p++, count++
    ) {
        last |= (*p) << (count * 8);
    }
    
    hash *= 1099511628211ull;
    hash ^= last;
    
    return hash;
};

Hasher &
CUA::getDefaultHasher()
{
    return FNVHasher;
}