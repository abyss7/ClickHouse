#pragma once

class Token
{
public:
    enum Type
    {
        INVALID,

        // one symbol
        PLUS,           // +
        MINUS,          // -
        ASTERISK,       // *
        ASSIGNMENT,     // =

        COMMA, // ,
        DOT, // .

        LEFT_PAREN,     // (
        RIGHT_PAREN,    // )
        LEFT_BRACKET,   // [
        RIGHT_BRACKET,  // ]

        // one-o-two symbol
        // TODO: all comparisons

        // two symbol
        // TODO

        // multi symbol
        NUMBER,         // 12345 123.45 .12345 1.23e45
        STRING,         // 'abc'
        COMMENT,        // -- … \n

        TYPE_SIZE
    };
};
