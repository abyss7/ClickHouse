#pragma once

#include "Base.h"

namespace DB
{
namespace AST
{

class ColumnExpr : public Base
{

};

using ColumnExprPtr = std::shared_ptr<ColumnExpr>;

} // namespace AS
} // namespace DB
