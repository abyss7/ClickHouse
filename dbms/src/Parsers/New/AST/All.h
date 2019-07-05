#pragma once

#include "Base.h"
#include "BinaryOp.h"
#include "ColumnExpr.h"
#include "ColumnExprList.h"
#include "ColumnFunc.h"
#include "ColumnIdentifier.h"
#include "Literal.h"
#include "Query.h"
#include "QueryList.h"
#include "SelectQuery.h"
#include "TableExpr.h"
#include "TableExprList.h"
#include "TableFunc.h"
#include "TableIdentifier.h"
#include "UnaryOp.h"

namespace DB
{
namespace AST
{

// NOTE: we can't do forward declaration since the compiler won't know about class inheritance
//       and will forbid downcasts like:
//
//           void foo(Ptr a);
//           QueryPtr b;
//           foo(b);
//

#define DECLARE_PTR(T) using T##Ptr = std::shared_ptr<T>;
DECLARE_PTR(ColumnFunc);
DECLARE_PTR(ColumnIdentifier);
DECLARE_PTR(Literal);
DECLARE_PTR(Query);
DECLARE_PTR(QueryList);
DECLARE_PTR(SelectQuery);
DECLARE_PTR(TableFunc);
DECLARE_PTR(TableIdentifier);
#undef DECLARE_PTR

} // namespace AST
} // namespace DB
