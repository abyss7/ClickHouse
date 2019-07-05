#pragma once

#include "TableExprList.h"

namespace DB
{
namespace AST
{

class TableFunc : public TableExpr
{
public:
    TableFunc(const Token & name, TableExprListPtr args);
};

} // namespace AST
} // namespace DB
