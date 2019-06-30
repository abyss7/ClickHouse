#pragma once

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

    inline Location currentLocation() const { return Location(line, column, pos + 1); }

    inline char current() const { return input[pos]; }
    char lookAhead() const; // returns '\0' if there is nothing ahead

    void advance(UInt64 step = 1);
    void newLine();

    bool isOneSymbolToken(Token::Type & type) const;
    bool isOneOrTwoSymbolsToken(Token::Type & type) const;
    bool isTwoSymbolsToken(Token::Type & type) const;
    bool isComment() const;
    bool isNumber() const;
    bool isString() const;
    bool isIdentifierOrKeyword() const;

    Token consumeComment();
    Token consumeNumber();
    Token consumeString();
    Token consumeIdentifierOrKeyword();

    const String & input;

    // Current location
    UInt64 pos = 0;
    UInt64 line = 1;
    UInt64 column = 1;
};

}
