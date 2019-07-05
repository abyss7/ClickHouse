#pragma once

#include "TableExpr.h"

namespace DB
{
namespace AST
{

class TableIdentifier : public TableExpr
{
public:
    explicit TableIdentifier(const Token & short_name);
    TableIdentifier(const Token & short_name, const Token & database_name);
};

} // namespace AST
} // namespace DB
