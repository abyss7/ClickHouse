#pragma once

#include "ColumnExpr.h"

namespace DB
{
namespace AST
{

class ColumnIdentifier : public ColumnExpr
{
public:
    explicit ColumnIdentifier(const Token & short_name);
    ColumnIdentifier(const Token & column_name, const Token & table_name);
    ColumnIdentifier(const Token & column_name, const Token & table_name, const Token & database_name);
};

} // namespace AST
} // namespace DB
