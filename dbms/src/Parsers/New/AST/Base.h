#pragma once

#include <Parsers/New/Token.h>

#include <memory>

namespace DB
{
namespace AST
{

class Base
{

};

using Ptr = std::shared_ptr<Base>;

template <class T, Token::Type Separator>
class List : public Base
{
public:
    void append(Ptr & node);
};

} // namespace AST
} // namespace DB
