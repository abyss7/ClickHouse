#pragma once

#include "ColumnExpr.h"

namespace DB
{
namespace AST
{

class UnaryOp : public ColumnExpr
{
public:
    UnaryOp(const Token & op, AST::ColumnExprPtr arg);
};

} // namespace AST
} // namespace DB
