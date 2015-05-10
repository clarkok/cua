#ifndef _CUA_TABLE_H_
#define _CUA_TABLE_H_

#include <map>
#include <list>
#include <iterator>

#include "../config.h"
#include "value.h"

namespace CUA {
    class Table
    {
        typedef std::pair<Value *, Reference> Pair;
        std::map<Config::T_OID, std::list<Pair> > table;
        std::uint64_t size_ = 0;
    public:
        struct Iterator
        {
            Table *owner;
            decltype(table.begin()) map_iter;
            decltype(table.begin()->second.begin()) list_iter;
            
            Iterator (
                Table *owner,
                decltype(map_iter) map_iter,
                decltype(list_iter) list_iter = decltype(list_iter)()
            )
            : owner(owner), map_iter(map_iter), list_iter(list_iter)
            { }
            
            Iterator
            next() const
            {
                auto next_list_iter = std::next(list_iter);
                auto next_map_iter = std::next(map_iter);
                if (next_list_iter != map_iter->second.end())
                    return Iterator(owner, map_iter, next_list_iter);
                else if (next_map_iter != owner->table.end())
                    return Iterator(
                        owner,
                        next_map_iter,
                        next_map_iter->second.begin());
                else
                    return Iterator(owner, next_map_iter);
            }
            
            bool
            operator == (const Iterator &b) const
            { return map_iter == b.map_iter && list_iter == b.list_iter; }
            
            Value *
            key() const
            { return list_iter->first; }
            
            Reference
            value() const
            { return list_iter->second; }
        };
    
        Reference get(Value *) const;
        Reference set(Value *, Reference);
        void erase(Value *);
        
        Reference getFromNumber(NumberValue *) const;
        Reference getFromString(StringValue *) const;
        Reference getFromTable(TableValue *) const;
        Reference getFromBoolean(BooleanValue *) const;
        
        Reference setFromNumber(NumberValue *, Reference);
        Reference setFromString(StringValue *, Reference);
        Reference setFromTable(TableValue *, Reference);
        Reference setFromBoolean(BooleanValue *, Reference);
        
        void eraseFromNumber(NumberValue *);
        void eraseFromString(StringValue *);
        void eraseFromTable(TableValue *);
        void eraseFromBoolean(BooleanValue *);
        
        Iterator begin()
        { return Iterator(this, table.begin(), table.begin()->second.begin()); }
        
        Iterator end()
        { return Iterator(this, table.end()); }
        
        inline decltype(size_)
        size() const
        { return size_; }
    };
};

#endif // _CUA_TABLE_H_