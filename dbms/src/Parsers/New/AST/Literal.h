#pragma once

#include "ColumnExpr.h"

namespace DB
{
namespace AST
{

class Literal : public ColumnExpr
{
public:
    explicit Literal(const Token & value);
};

} // namespace AST
} // namespace DB
