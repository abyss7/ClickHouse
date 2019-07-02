#pragma once

#include <Parsers/New/AST/Base.h>

namespace DB {
namespace AST {

class UnaryOp : public Base
{
public:
    UnaryOp(const Token & op, AST::Ptr arg);
};

} // namespace AST
} // namespace DB
