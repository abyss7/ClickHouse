#pragma once

#include <Parsers/New/AST/Query.h>

namespace DB {
namespace AST {

// SELECT {ColumnList} FROM {TableList} WHERE {Contidion};

class SelectQuery : public Query
{
public:
    void setColumnList(AST::Ptr expr_list);
    void setTableList(AST::Ptr expr_list);
    void setCondition(AST::Ptr expr);
};

} // namespace AST
} // namespace DB
