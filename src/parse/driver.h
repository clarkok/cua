#ifndef _CUA_PARSE_DRIVER_H_
#define _CUA_PARSE_DRIVER_H_

#include <string>

#include "../ast.h"

class Driver
{
    const char *content;
public:
    Driver(const char *content)
    : content(content)
    { }
    
    virtual ~Driver()
    {
        // FIXME deallocate AST
    }
    
    void scanner_begin(const char *content = nullptr);
    void scanner_end();
    
    int parse();
    
    CUA::ASTNode *root = nullptr;
};

#endif // _CUA_PARSE_DRIVER_H_