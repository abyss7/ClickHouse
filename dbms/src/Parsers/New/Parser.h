#pragma once

#include <Parsers/New/AST/All.h>

namespace DB
{

class Parser
{
public:
    using Iterator = std::vector<Token>::const_iterator;

    Parser(Iterator begin, Iterator end);

    AST::Ptr parse();

    AST::QueryListPtr parseQueryList();
    AST::QueryPtr parseQuery();
    AST::SelectQueryPtr parseSelectQuery();

    AST::ColumnExprListPtr parseColumnExprList();
    AST::ColumnExprPtr parseColumnExpr(UInt8 precedence = 0u);
    AST::ColumnFuncPtr parseColumnFunc();
    AST::ColumnIdentifierPtr parseColumnIdentifier();

    AST::TableExprListPtr parseTableExprList();
    AST::TableExprPtr parseTableExpr();
    AST::TableFuncPtr parseTableFunc();
    AST::TableIdentifierPtr parseTableIdentifier();

    AST::LiteralPtr parseLiteral();

private:
    const Token & expect(Token::Type expected_type) const;
    const Token & expect(const Token::TypeList & expected_types) const;
    const Token & expect(const std::string & expected_keyword) const;

    bool next(Token::Type type, UInt32 advance = 0u) const;
    bool next(const Token::TypeList & types) const;
    bool next(const std::string & keyword) const;

    const Token & consume(Token::Type type);
    const Token & consume(const Token::TypeList & types);
    const Token & consume(const std::string & keyword);

    Iterator current;
    const Iterator end;
};

} // namespace DB
