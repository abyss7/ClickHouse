#include <Parsers/New/AST/SystemQuery.h>

#include <Parsers/ASTSystemQuery.h>
#include <Parsers/New/AST/Identifier.h>
#include <Parsers/New/ParseTreeVisitor.h>


namespace DB::AST
{

// static
PtrTo<SystemQuery> SystemQuery::createFetches(bool stop, PtrTo<TableIdentifier> identifier)
{
    PtrTo<SystemQuery> query(new SystemQuery(QueryType::FETCHES, {identifier}));
    query->stop = stop;
    return query;
}

// static
PtrTo<SystemQuery> SystemQuery::createMerges(bool stop, PtrTo<TableIdentifier> identifier)
{
    PtrTo<SystemQuery> query(new SystemQuery(QueryType::MERGES, {identifier}));
    query->stop = stop;
    return query;
}

// static
PtrTo<SystemQuery> SystemQuery::createSync(PtrTo<TableIdentifier> identifier)
{
    return PtrTo<SystemQuery>(new SystemQuery(QueryType::SYNC, {identifier}));
}

SystemQuery::SystemQuery(QueryType type, PtrList exprs) : query_type(type)
{
    children = exprs;

    (void)query_type; // TODO
}

ASTPtr SystemQuery::convertToOld() const
{
    auto query = std::make_shared<ASTSystemQuery>();

    // TODO

    return query;
}

}

namespace DB
{

using namespace AST;

antlrcpp::Any ParseTreeVisitor::visitSystemStmt(ClickHouseParser::SystemStmtContext *ctx)
{
    if (ctx->SYNC()) return SystemQuery::createSync(visit(ctx->tableIdentifier()).as<PtrTo<TableIdentifier>>());
    if (ctx->MERGES()) return SystemQuery::createMerges(!!ctx->STOP(), visit(ctx->tableIdentifier()));
    if (ctx->FETCHES()) return SystemQuery::createFetches(!!ctx->STOP(), visit(ctx->tableIdentifier()));
    __builtin_unreachable();
}

}
