#pragma once

#include <Core/Types.h>
#include <Parsers/New/Token.h>

namespace DB
{

class Lexer
{
public:
    explicit Lexer(const String & input);

    std::vector<Token> tokenize();

private:
    Token next(bool & done);

    Location currentLocation() const;

    char current() const;
    char lookAhead() const; // returns '\0' if there is nothing ahead

    const String & input;
    size_t pos = 0;
};

}
