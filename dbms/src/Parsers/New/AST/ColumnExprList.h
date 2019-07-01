#pragma once

#include <Parsers/New/AST/ColumnExpr.h>

namespace DB {
namespace AST {

class ColumnExprList : public List<ColumnExpr, Token::COMMA>
{

};

} // namespace AST
} // namespace DB
