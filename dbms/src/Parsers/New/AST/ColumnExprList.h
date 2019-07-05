#pragma once

#include "ColumnExpr.h"

namespace DB
{
namespace AST
{

class ColumnExprList : public List<ColumnExpr, Token::COMMA>
{

};

using ColumnExprListPtr = std::shared_ptr<ColumnExprList>;

} // namespace AST
} // namespace DB
