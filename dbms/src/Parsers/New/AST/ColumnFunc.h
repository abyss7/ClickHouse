#pragma once

#include "ColumnExprList.h"

namespace DB
{
namespace AST
{

class ColumnFunc : public ColumnExpr
{
public:
    ColumnFunc(const Token & name, ColumnExprListPtr args);
};

} // namespace AST
} // namespace DB
