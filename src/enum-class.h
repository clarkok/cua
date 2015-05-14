#ifndef _CUA_ENUM_CLASS_H_
#define _CUA_ENUM_CLASS_H_

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

namespace CUA {
    namespace Reflect {
        template <typename T>
        struct reflect_type
        { typedef T type; };
        
        template <typename T_Reflector>
        typename reflect_type<T_Reflector>::type *get_reflector()
        { return nullptr; }
    }
}

#define ENUM_CLASS(TypeName, ...)                                   \
    enum class TypeName { __VA_ARGS__ };                            \
    class Reflector##TypeName                                       \
    {                                                               \
        ::std::vector<::std::string> _to_string;                    \
        ::std::map<::std::string, TypeName> _from_string;           \
    public:                                                         \
        inline Reflector##TypeName()                                \
        {                                                           \
            char LITERAL[] = #__VA_ARGS__;                          \
            char *tk = nullptr;                                     \
            for (                                                   \
                tk = std::strtok(LITERAL, ", ");                    \
                tk;                                                 \
                tk = std::strtok(nullptr, ", ")                     \
            ) {                                                     \
                _from_string[tk] =                                  \
                    static_cast<TypeName>(_to_string.size());       \
                _to_string.push_back(tk);                           \
            }                                                       \
        }                                                           \
        std::string toString(TypeName value) const                  \
        { return _to_string[static_cast<int>(value)]; }             \
        TypeName fromString(std::string value) const                \
        { return _from_string.at(value); }                          \
    };                                                              \
    template <> inline                                              \
    CUA::Reflect::reflect_type<Reflector##TypeName>::type *         \
    CUA::Reflect::get_reflector<Reflector##TypeName>()              \
    { static Reflector##TypeName reflector; return &reflector; }
    
#define ERE(TypeName)   \
    (::CUA::Reflect::get_reflector<Reflector##TypeName>())

#endif // _CUA_ENUM_CLASS_H_