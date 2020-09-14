#include <iomanip>
#include <Parsers/ASTInsertQuery.h>
#include <Parsers/ASTFunction.h>
#include <Common/quoteString.h>
#include <IO/WriteHelpers.h>


namespace DB
{

namespace ErrorCodes
{
    extern const int INVALID_USAGE_OF_INPUT;
}


ASTInsertQuery::ASTInsertQuery(const StorageID & id)
{
    table = std::make_shared<ASTTableIdentifier>(id);
}

String ASTInsertQuery::getID(char delim) const
{
    if (table)
        return "InsertQuery" + (delim + table->as<ASTTableIdentifier>()->getDatabaseName()) + delim
            + table->as<ASTTableIdentifier>()->getTableName();
    else if (table_function)
        return "InsertQuery" + (delim + table_function->getID(delim));
    __builtin_unreachable();
}

void ASTInsertQuery::formatImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const
{
    frame.need_parens = false;

    settings.ostr << (settings.hilite ? hilite_keyword : "") << "INSERT INTO ";
    if (table_function)
    {
        settings.ostr << (settings.hilite ? hilite_keyword : "") << "FUNCTION ";
        table_function->formatImpl(settings, state, frame);
    }
    else
    {
        auto * table_ptr = table->as<ASTTableIdentifier>();
        settings.ostr << (settings.hilite ? hilite_none : "")
                      << (!table_ptr->getDatabaseName().empty() ? backQuoteIfNeed(table_ptr->getDatabaseName()) + "." : "")
                      << backQuoteIfNeed(table_ptr->getTableName());
    }

    if (columns)
    {
        settings.ostr << " (";
        columns->formatImpl(settings, state, frame);
        settings.ostr << ")";
    }

    if (select)
    {
        settings.ostr << " ";
        select->formatImpl(settings, state, frame);
    }
    else if (watch)
    {
        settings.ostr << " ";
        watch->formatImpl(settings, state, frame);
    }
    else
    {
        if (!format.empty())
        {
            settings.ostr << (settings.hilite ? hilite_keyword : "") << " FORMAT " << (settings.hilite ? hilite_none : "") << format;
        }
        else
        {
            settings.ostr << (settings.hilite ? hilite_keyword : "") << " VALUES" << (settings.hilite ? hilite_none : "");
        }
    }

    if (settings_ast)
    {
        settings.ostr << (settings.hilite ? hilite_keyword : "") << "SETTINGS " << (settings.hilite ? hilite_none : "");
        settings_ast->formatImpl(settings, state, frame);
    }
}


static void tryFindInputFunctionImpl(const ASTPtr & ast, ASTPtr & input_function)
{
    if (!ast)
        return;
    for (const auto & child : ast->children)
        tryFindInputFunctionImpl(child, input_function);

    if (const auto * table_function_ast = ast->as<ASTFunction>())
    {
        if (table_function_ast->name == "input")
        {
            if (input_function)
                throw Exception("You can use 'input()' function only once per request.", ErrorCodes::INVALID_USAGE_OF_INPUT);
            input_function = ast;
        }
    }
}


void ASTInsertQuery::tryFindInputFunction(ASTPtr & input_function) const
{
    tryFindInputFunctionImpl(select, input_function);
}

}
