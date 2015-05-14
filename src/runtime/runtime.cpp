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

std::string
Runtime::newLiteral(Value *v)
{
    std::string name = Config::SCOPE_LITERAL_PREFIX 
        + std::to_string(++literal_count);
    getGlobalScope()->getReferenceByName(name)->reset(v);
    return name;
}