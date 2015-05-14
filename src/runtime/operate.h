#ifndef _CUA_OPERATE_H_
#define _CUA_OPERATE_H_

#include "runtime.h"
#include "value.h"

namespace CUA {
    namespace Operate {
        Reference add(Value *, Value *);
        Reference addnn(NumberValue *, NumberValue *);
        
        Reference sub(Value *, Value *);
        Reference subnn(NumberValue *, NumberValue *);
        
        Reference mul(Value *, Value *);
        Reference mulnn(NumberValue *, NumberValue *);
        
        Reference div(Value *, Value *);
        Reference divnn(NumberValue *, NumberValue *);
        
        Reference mod(Value *, Value *);
        Reference modnn(NumberValue *, NumberValue *);
        
        Reference index(Value *, Value *);
        Reference copy(Value *);
    }
}

#endif // _CUA_OPERATE_H_