#pragma once

#include <Parsers/New/AST/Base.h>
#include <Parsers/New/Token.h>

namespace DB
{

class Parser
{
public:
    using Iterator = std::vector<Token>::const_iterator;

    Parser(Iterator begin, Iterator end);

    AST::Ptr parse();

    AST::Ptr parseQueryList();
    AST::Ptr parseQuery();
    AST::Ptr parseSelectQuery();

    AST::Ptr parseColumnExprList();
    AST::Ptr parseColumnExpr(UInt8 precedence = 0u);

    AST::Ptr parseTableExprList();
    AST::Ptr parseTableExpr();

private:
    const Token & expect(const Token::TypeList & expected_types) const;
    const Token & expect(const std::string & expected_keyword) const;

    bool next(Token::Type type, UInt32 advance = 0u);
    bool next(const Token::TypeList & types) const;
    bool next(const std::string & keyword) const;

    const Token & consume(const Token::TypeList & types);
    const Token & consume(const std::string & keyword);

    Iterator current;
    const Iterator end;
};

} // namespace DB
