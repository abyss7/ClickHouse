#pragma once

#include "ColumnExpr.h"

namespace DB
{
namespace AST
{

class BinaryOp : public ColumnExpr
{
public:
    BinaryOp(const Token & op, AST::ColumnExprPtr arg1, AST::ColumnExprPtr arg2);
};

} // namespace AST
} // namespace DB
