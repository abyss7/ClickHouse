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
        // TODO
    }
    else if (isTwoSymbolsToken(token_type))
    {
        advance(2);
        return Token(location, token_type);
    }
    else if (isComment())
    {
        return consumeComment();
    }
    else if (isNumber())
    {
        return consumeNumber();
    }
    else if (isString())
    {
        return consumeString();
    }
    else if (isIdentifierOrKeyword())
    {
        return consumeIdentifierOrKeyword();
    }

    // TODO: throw exception about unexpected symbol
    throw std::logic_error("Unexpected symbol");

    // TODO: NOT_REACHED()
    __builtin_unreachable();
}

char Lexer::lookAhead() const
{
    if (pos + 1 == input.size())
    {
        return '\0';
    }

    return input[pos + 1];
}

void Lexer::advance(UInt64 step)
{
    column += step;
    pos += step;
}

void Lexer::newLine()
{
    ++line;
    column = 1;
    ++pos;
}

bool Lexer::isOneSymbolToken(Token::Type & type) const
{
    switch(current())
    {
        case '+':
            type = Token::PLUS;
            return true;
        case '*':
            type = Token::ASTERISK;
            return true;
        case '/':
            type = Token::SLASH;
            return true;
        case '%':
            type = Token::PERCENT;
            return true;
        case '?':
            type = Token::QUERY;
            return true;
        case ',':
            type = Token::COMMA;
            return true;
        case '.':
            type = Token::DOT;
            return true;
        case ':':
            type = Token::COLON;
            return true;
        case ';':
            type = Token::SEMICOLON;
            return true;
        case '(':
            type = Token::LEFT_PAREN;
            return true;
        case ')':
            type = Token::RIGHT_PAREN;
            return true;
        case '[':
            type = Token::LEFT_BRACKET;
            return true;
        case ']':
            type = Token::RIGHT_BRACKET;
            return true;
    }

    return false;
}

bool Lexer::isOneOrTwoSymbolsToken(Token::Type & type) const
{
    switch(current())
    {
        case '-':
            type = Token::MINUS;
            return true;
        case '=':
            type = Token::ASSIGNMENT;
            return true;
        case '<':
            type = Token::STRICTLY_LESS;
            return true;
        case '>':
            type = Token::STRICTLY_GREATER;
            return true;
    }

    return false;
}

bool Lexer::isTwoSymbolsToken(Token::Type & type) const
{
    switch(current())
    {
        case '!':
            if (lookAhead() == '=')
            {
                type = Token::NOT_EQUAL;
                return true;
            }
            break;
        case '|':
            if (lookAhead() == '|')
            {
                type = Token::CONCAT;
                return true;
            }
            break;
    }

    return false;
}

bool Lexer::isComment() const
{
    return current() == '-' && lookAhead() == '-';
}

bool Lexer::isNumber() const
{
    return std::isdigit(current()) || (current() == '.' && std::isdigit(lookAhead()));
}

bool Lexer::isString() const
{
    return current() == '\'';
}

bool Lexer::isIdentifierOrKeyword() const
{
    return std::isalpha(current()) || current() == '_';
}

Token Lexer::consumeComment()
{
    auto location = currentLocation();

    while (pos < input.size() && current() != '\n')
        advance();

    auto begin = location.getByte(), end = currentLocation().getByte();
    return Token(location, Token::COMMENT, input.substr(begin - 1, end - begin));
}

Token Lexer::consumeNumber()
{
    auto location = currentLocation();

    while (pos < input.size() && std::isdigit(current()))
        advance();

    if (pos < input.size() && current() == '.')
        advance();

    while (pos < input.size() && std::isdigit(current()))
        advance();

    if (pos < input.size() && current() == 'e')
    {
        advance();
        if (pos < input.size() && current() == '-')
            advance();
    }

    while (pos < input.size() && std::isdigit(current()))
        advance();

    auto begin = location.getByte(), end = currentLocation().getByte();
    return Token(location, Token::NUMBER, input.substr(begin - 1, end - begin));
}

Token Lexer::consumeString()
{
    auto location = currentLocation();

    advance(); // consume starting quote

    while (pos < input.size() && current() != '\'' && current() != '\n')
        advance();

    if (pos == input.size() || current() != '\'')
        // TODO: throw exception about parsing error.
        throw std::logic_error("Unexpected symbol!");
    advance();

    auto begin = location.getByte(), end = currentLocation().getByte();
    return Token(location, Token::STRING, input.substr(begin - 1, end - begin));
}

Token Lexer::consumeIdentifierOrKeyword()
{
    auto location = currentLocation();

    advance(); // consume first symbol - we know it's good

    while (pos < input.size() && (isIdentifierOrKeyword() || std::isdigit(current())))
        advance();

    auto begin = location.getByte(), end = currentLocation().getByte();
    return Token(location, Token::IDENTIFIER, input.substr(begin - 1, end - begin));
}

}
