#include "runtime.h"
#include "scope.h"

using namespace CUA;

Scope*
Runtime::getGlobalScope()
{
    if (!global_scope)
        global_scope = new Scope(nullptr);
    return global_scope;
}

Scope*
Runtime::createScope()
{ return getGlobalScope()->createChildScope(); }