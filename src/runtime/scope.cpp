#include "../config.h"
#include "scope.h"

using namespace CUA;

Value *Scope::CHILD_SCOPE_KEY =
    getGlobalRuntime()->newString(Config::CHILD_SCOPE_KEY);