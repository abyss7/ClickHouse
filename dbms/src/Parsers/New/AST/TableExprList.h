#pragma once

#include <Parsers/New/AST/TableExpr.h>

namespace DB {
namespace AST {

class TableExprList : public List<TableExpr, Token::COMMA>
{

};

} // namespace AST
} // namespace DB
