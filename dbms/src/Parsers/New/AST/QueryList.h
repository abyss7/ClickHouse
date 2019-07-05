#pragma once

#include "Query.h"

namespace DB
{
namespace AST
{

class QueryList : public List<Query, Token::SEMICOLON>
{
};

} // namespace AST
} // namespace DB
