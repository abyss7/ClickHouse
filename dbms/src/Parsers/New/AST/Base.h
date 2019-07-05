#pragma once

#include <Parsers/New/Token.h>

namespace DB
{
namespace AST
{

class Base
{
private:
    LocationRange location;
};

using Ptr = std::shared_ptr<Base>;

template <class T, Token::Type Separator>
class List : public T
{
public:
    void append(Ptr node);
};

} // namespace AST
} // namespace DB
