#include "../config.h"
#include "scope.h"

using namespace CUA;

StringValue *Scope::CHILD_SCOPE_KEY =
    dynamic_cast<StringValue*>(
        getGlobalRuntime()->newString(Config::CHILD_SCOPE_KEY).get());
    
StringValue *Scope::UPPER_SCOPE_KEY =
    dynamic_cast<StringValue*>(
        getGlobalRuntime()->newString(Config::UPPER_SCOPE_KEY).get());