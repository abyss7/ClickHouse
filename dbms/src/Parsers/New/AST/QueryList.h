#pragma once

#include <Parsers/New/AST/Query.h>

namespace DB
{
namespace AST
{

class QueryList : public List<Query, Token::SEMICOLON>
{
};

} // namespace AST
} // namespace DB
