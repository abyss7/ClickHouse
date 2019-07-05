#pragma once

#include "ColumnExprList.h"
#include "Query.h"
#include "TableExprList.h"

namespace DB
{
namespace AST
{

// SELECT {ColumnList} FROM {TableList} WHERE {Contidion};

class SelectQuery : public Query
{
public:
    void setColumnList(AST::ColumnExprListPtr expr_list);
    void setTableList(AST::TableExprListPtr expr_list);
    void setCondition(AST::ColumnExprPtr expr);
};

} // namespace AST
} // namespace DB
