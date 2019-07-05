#pragma once

#include "TableExpr.h"

namespace DB
{
namespace AST
{

class TableExprList : public List<TableExpr, Token::COMMA>
{

};

using TableExprListPtr = std::shared_ptr<TableExprList>;

} // namespace AST
} // namespace DB
