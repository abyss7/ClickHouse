#pragma once

#include <Parsers/New/AST/Base.h>

namespace DB {
namespace AST {

class BinaryOp : public Base
{
public:
    BinaryOp(const Token & op, AST::Ptr arg1, AST::Ptr arg2);
};

} // namespace AST
} // namespace DB
