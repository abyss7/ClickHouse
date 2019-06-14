#include <Parsers/New/Lexer.h>

namespace DB
{
Lexer::Lexer(const String & input_) : input(input_)
{
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    bool done = false;
    while (!done)
    {
        tokens.emplace_back(next(done));
    }

    return tokens;
}

Token Lexer::next(bool & done)
{
    // Trim all the whitespace before token.
    for (bool token_found = false; pos < input.size() && !token_found;)
    {
        switch (current())
        {
            case ' ':
            case '\t':
            case '\r':
            {
                advance();
                continue;
            }
            case '\n':
            {
                newLine();
                continue;
            }
            default:
                token_found = true;
        }
    }

    // Check that current position is inside contents.
    if (pos == input.size())
    {
        done = true;
        return Token();
    }

    auto location = currentLocation();

    // Consume the token.
    Token::Type token_type;
    if (isOneSymbolToken(token_type))
    {
        advance();
        return Token(location, token_type);
    }
    else if (isOneOrTwoSymbolsToken(token_type))
    {
    }
    else if (isTwoSymbolsToken(token_type))
    {
        advance(2);
        return Token(location, token_type);
    }
    else if (isInteger())
    {
        return consumeInteger();
    }
    else if (isString())
    {
        return consumeString();
    }
    else if (isIdentifierOrKeyword())
    {
        return consumeIdentifierOrKeyword();
    }
    else if (isComment())
    {
        return consumeComment();
    }
}

}
