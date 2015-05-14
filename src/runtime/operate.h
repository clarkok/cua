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
        
        Reference slt(Value *, Value *);
        Reference sltnn(NumberValue *, NumberValue *);
        Reference sltss(StringValue *, StringValue *);
        
        Reference sle(Value *, Value *);
        Reference slenn(NumberValue *, NumberValue *);
        Reference sless(StringValue *, StringValue *);
        
        Reference seq(Value *, Value *);
        
        Reference land(Value *, Value *);
        Reference landbb(BooleanValue *, BooleanValue *);
        
        Reference lor(Value *, Value *);
        Reference lorbb(BooleanValue *, BooleanValue *);
        
        Reference lnot(Value *);
        Reference lnotb(BooleanValue *);
        
        Reference index(Value *, Value *);
        Reference copy(Value *);
    }
}

#endif // _CUA_OPERATE_H_