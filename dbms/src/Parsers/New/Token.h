#pragma once

#include <Parsers/New/Location.h>

#include <list>
#include <map>

namespace DB
{

class Token
{
public:
    enum Type
    {
        INVALID,

        // one symbol
        PLUS,               // +
        MINUS,              // -
        ASTERISK,           // *
        ASSIGNMENT,         // =
        SLASH,              // /
        PERCENT,            // %
        QUERY,              // ?

        STRICTLY_LESS,      // <
        STRICTLY_GREATER,   // >

        COMMA,              // ,
        DOT,                // .
        COLON,              // :
        SEMICOLON,          // ;

        LEFT_PAREN,         // (
        RIGHT_PAREN,        // )
        LEFT_BRACKET,       // [
        RIGHT_BRACKET,      // ]

        // one-o-two symbol
        EQUAL_EQUAL,        // ==
        LESS_EQUAL,         // <=
        GREATER_EQUAL,      // >=

        ARROW,              // ->

        // two symbol
        NOT_EQUAL,          // !=
        CONCAT,             // ||

        // multi symbol
        IDENTIFIER,
        NUMBER,             // 12345 123.45 .12345 1.23e45 1.23e-45
        STRING,             // 'abc'
        COMMENT,            // -- … \n

        // We need a separate section for keyword-ops to help with precedence

        // keywords
        NEGATIVE,           // unary -
        NOT,                // unary NOT

        TYPE_SIZE
    };

    using TypeList = std::list<Type>;

    Token() = default;
    Token(const Location & location, Type type, const String & value = {});

    Token(Token &&) = default;
    Token(const Token &) = delete;
    Token & operator=(const Token &) = delete;

    const Location & getLocation() const { return location; }
    Type getType() const { return type; }
    const std::string & getValue() const { return value; }

    auto getPrecedence() const { return precedence.at(type); }

    static TypeList literals();
    static TypeList binaryOps();

private:
    const Location location = {};
    const Type type = INVALID;
    const String value; // FIXME: can be replaced with a string_view

    static const std::map<Type, UInt8> precedence;
};

}
