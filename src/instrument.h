#ifndef _CUA_INSTRUMENT_H_
#define _CUA_INSTRUMENT_H_

#include <list>

#include "enum-class.h"

namespace CUA {
    ENUM_CLASS(InstrumentType,
        I_UNKNOWN,
        I_ADD,
        I_SUB,
        I_MUL,
        I_DIV,
        I_MOD,
        I_INDEX,
        I_MOVE,
        I_COPY,
        I_LABEL,
        I_GOTO
    );
    
    struct Instrument
    {
        typedef InstrumentType Type;
        
        Type type;
        std::string rs;
        std::string rt;
        std::string rd;
        
        Instrument(
            Type type,
            std::string rd = "",
            std::string rs = "",
            std::string rt = ""
        )
        : type(type), rd(rd), rs(rs), rt(rt)
        { }
    };
}

#endif // _CUA_INSTRUMENT_H_