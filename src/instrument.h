#ifndef _CUA_INSTRUMENT_H_
#define _CUA_INSTRUMENT_H_

#include <list>

#include "enum-class.h"

namespace CUA {
    ENUM_CLASS(InstrumentType,
        I_UNKNOWN,
        I_ADD,      // rd = rs + rt
        I_SUB,      // rd = rs - rt
        I_MUL,      // rd = rs * rt
        I_DIV,      // rd = rs / rt
        I_MOD,      // rd = rs % rt
        I_LAND,     // rd = rs && rt
        I_LOR,      // rd = rs || rt
        I_LNOT,     // rd = !rs
        I_EQ,       // rd = (rs == rt)
        I_INDEX,    // rd = rs[rt]
        I_MOVE,     // rd = rs
        I_COPY,     // rd = new rs
        I_LABEL,    // rd:
        I_GOTO,     // goto rd
        I_GOTOIF    // if rs goto rd
    );
    
    struct Instrument
    {
        typedef InstrumentType Type;
        
        Type type;
        std::string rd;
        std::string rs;
        std::string rt;
        
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