#pragma once

#include "Base.h"

namespace DB
{
namespace AST
{

class TableExpr : public Base
{

};

using TableExprPtr = std::shared_ptr<TableExpr>;

} // namespace AST
} // namespace DB
