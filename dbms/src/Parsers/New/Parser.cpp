#include <Parsers/New/Parser.h>

#include <Parsers/New/AST/BinaryOp.h>
#include <Parsers/New/AST/ColumnExprList.h>
#include <Parsers/New/AST/QueryList.h>
#include <Parsers/New/AST/SelectQuery.h>
#include <Parsers/New/AST/TableExprList.h>
#include <Parsers/New/AST/UnaryOp.h>

namespace DB {

AST::Ptr Parser::parse()
{
    auto result = parseQueryList();
    expect(Token::INVALID);
    return result;
}

AST::Ptr Parser::parseQueryList()
{
    auto list = std::make_shared<AST::QueryList>();
    bool first = true;

    while (current != end)
    {
        if (!first)
            consume(Token::SEMICOLON);

        AST::Ptr query = parseQuery();
        if (!query)
        {
            // Query list is over
            break;
        }
        list->append(query);
        first = false;
    }

    return list;
}

AST::Ptr Parser::parseQuery()
{
    if (next("select"))
    {
        // FIXME: SELECT-query may start with WITH keyword.
        return parseSelectQuery();
    }

    // TODO: add all other queries here.

    return {};
}

AST::Ptr Parser::parseSelectQuery()
{
    auto select = std::make_shared<AST::SelectQuery>();

    consume("select");
    select->setColumnList(parseColumnExprList());

    if (next("from"))
    {
        consume("from");
        select->setTableList(parseTableExprList());
    }

    if (next("where"))
    {
        consume("where");
        select->setCondition(parseColumnExpr());
    }

    return select;
}

AST::Ptr Parser::parseColumnExprList()
{
    auto list = std::make_shared<AST::ColumnExprList>();
    auto expr = parseColumnExpr();

    while (next(Token::COMMA))
    {
        list->append(expr);
        consume(Token::COMMA);
        expr = parseColumnExpr();
    }

    if (expr)
        list->append(expr);

    return list;
}

AST::Ptr Parser::parseColumnExpr(UInt8 precedence)
{
    AST::Ptr left;

    if (next(Token::IDENTIFIER))
    {
        if (next("not"))
        {
            Token not_token(consume("not").getLocation(), Token::NOT);
            // FIXME: DCHECK(precedence <= not_precedence);
            return std::make_shared<AST::UnaryOp>(not_token, parseColumnExpr(not_token.getPrecedence()));
        }
        else if (next(Token::LEFT_PAREN, 1))
        {
            left = parseColumnFuncCall();
        }
        else
        {
            left = parseColumnIdentifier();
        }
    }
    else if (next(Token::MINUS))
    {
        Token minus_token(consume(Token::MINUS).getLocation(), Token::NEGATIVE);
        // FIXME: DCHECK(precedence <= minus_precedence);
        return std::make_shared<AST::UnaryOp>(minus_token, parseColumnExpr(minus_token.getPrecedence()));
    }
    else if (next(Token::LEFT_PAREN))
    {
        consume(Token::LEFT_PAREN);
        left = parseColumnExpr();
        consume(Token::RIGHT_PAREN);
    }
    else if (next(Token::literals()))
    {
        left = parseLiteral();
    }
    else
    {
        return left;
    }

    while (next(Token::binaryOps()))
    {
        if (expect(Token::binaryOps()).getPrecedence() <= precedence)
        {
            return left;
        }

        const auto & op = consume(Token::binaryOps());
        auto right = parseColumnExpr(op.getPrecedence());
        left = std::make_shared<AST::BinaryOp>(op, left, right);
    }

    return left;
}

AST::Ptr Parser::parseTableExprList()
{
    auto list = std::make_shared<AST::TableExprList>();
    auto expr = parseTableExpr();

    while (next(Token::COMMA))
    {
        list->append(expr);
        consume(Token::COMMA);
        expr = parseTableExpr();
    }

    if (expr)
        list->append(expr);

    return list;
}

AST::Ptr Parser::parseTableExpr()
{
    AST::Ptr left;

    if (next(Token::IDENTIFIER))
    {
        if (next(Token::LEFT_PAREN, 1))
        {
            left = parseTableFuncCall();
        }
        else
        {
            left = parseTableIdentifier();
        }
    }
    else if (next(Token::LEFT_PAREN))
    {
        consume(Token::LEFT_PAREN);
        left = parseTableExpr();
        consume(Token::RIGHT_PAREN);
    }

    return left;
}

bool Parser::next(Token::Type type, UInt32 advance) const
{
    if (current + advance == end)
        return false;
    return (current + advance)->getType() == type;
}

bool Parser::next(const Token::TypeList & types) const
{
    for (auto type : types)
        if (next(type))
            return true;
    return false;
}

bool Parser::next(const std::string & keyword) const
{
    // FIXME: compare to_lower() token value.
    return next(Token::IDENTIFIER) && (current + 1)->getValue() == keyword;
}

const Token & Parser::consume(const Token::TypeList & types)
{
    const auto & token = expect(types);
    ++current;
    return token;
}

const Token & Parser::consume(const std::string & keyword)
{
    const auto & token = expect(keyword);
    ++current;
    return token;
}

} // namespace DB
