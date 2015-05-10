#include "value.h"
#include "table.h"

using namespace CUA;

Config::T_OID TableValue::counter = 0;

TableValue::~TableValue()
{ delete ptr; }