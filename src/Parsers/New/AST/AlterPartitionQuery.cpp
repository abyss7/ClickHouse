#include <Parsers/New/AST/AlterPartitionQuery.h>

#include <Parsers/New/AST/Identifier.h>

#include <Parsers/New/ParseTreeVisitor.h>


namespace DB::AST
{

// static
PtrTo<AlterPartitionClause> AlterPartitionClause::createAttach(PtrTo<PartitionExprList> list, PtrTo<TableIdentifier> identifier)
{
    return PtrTo<AlterPartitionClause>(new AlterPartitionClause(ClauseType::ATTACH, {list, identifier}));
}

// static
PtrTo<AlterPartitionClause> AlterPartitionClause::createDetach(PtrTo<PartitionExprList> list)
{
    return PtrTo<AlterPartitionClause>(new AlterPartitionClause(ClauseType::DETACH, {list->begin(), list->end()}));
}

// static
PtrTo<AlterPartitionClause> AlterPartitionClause::createDrop(PtrTo<PartitionExprList> list)
{
    return PtrTo<AlterPartitionClause>(new AlterPartitionClause(ClauseType::DROP, {list->begin(), list->end()}));
}

// static
PtrTo<AlterPartitionClause> AlterPartitionClause::createReplace(PtrTo<PartitionExprList> list, PtrTo<TableIdentifier> identifier)
{
    return PtrTo<AlterPartitionClause>(new AlterPartitionClause(ClauseType::REPLACE, {list, identifier}));
}

AlterPartitionClause::AlterPartitionClause(ClauseType type, PtrList exprs) : clause_type(type)
{
    children = exprs;

    (void)clause_type; // TODO
}

AlterPartitionQuery::AlterPartitionQuery(PtrTo<TableIdentifier> identifier, PtrTo<List<AlterPartitionClause>> clauses)
{
    children.push_back(identifier);
    children.push_back(clauses);
}

}

namespace DB
{

using namespace AST;

antlrcpp::Any ParseTreeVisitor::visitAlterPartitionAttachClause(ClickHouseParser::AlterPartitionAttachClauseContext *ctx)
{
    auto from = ctx->tableIdentifier() ? visit(ctx->tableIdentifier()).as<PtrTo<TableIdentifier>>() : nullptr;
    return AlterPartitionClause::createAttach(visit(ctx->partitionClause()), from);
}

antlrcpp::Any ParseTreeVisitor::visitAlterPartitionDetachClause(ClickHouseParser::AlterPartitionDetachClauseContext *ctx)
{
    return AlterPartitionClause::createDetach(visit(ctx->partitionClause()));
}

antlrcpp::Any ParseTreeVisitor::visitAlterPartitionDropClause(ClickHouseParser::AlterPartitionDropClauseContext *ctx)
{
    return AlterPartitionClause::createDrop(visit(ctx->partitionClause()));
}

antlrcpp::Any ParseTreeVisitor::visitAlterPartitionReplaceClause(ClickHouseParser::AlterPartitionReplaceClauseContext *ctx)
{
    return AlterPartitionClause::createReplace(visit(ctx->partitionClause()), visit(ctx->tableIdentifier()));
}

}
