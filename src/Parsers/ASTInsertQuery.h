#pragma once

#include <Interpreters/StorageID.h>
#include <Parsers/ASTIdentifier.h>


namespace DB
{

/** INSERT query
  */
class ASTInsertQuery : public IAST
{
public:
    ASTInsertQuery() = default;
    explicit ASTInsertQuery(const StorageID & id);

    ASTPtr table;           // ASTTableIdentifier
    ASTPtr columns;         // ASTColumns
    String format;
    ASTPtr select;
    ASTPtr watch;
    ASTPtr table_function;  // ASTFunction
    ASTPtr settings_ast;

    /// Data to insert
    const char * data = nullptr;
    const char * end = nullptr;

    /// Query has additional data, which will be sent later
    bool has_tail = false;

    /// Try to find table function input() in SELECT part
    void tryFindInputFunction(ASTPtr & input_function) const;

    /** Get the text that identifies this element. */
    String getID(char delim) const override;

    ASTPtr clone() const override
    {
        auto res = std::make_shared<ASTInsertQuery>(*this);
        res->children.clear();

        if (columns) { res->columns = columns->clone(); res->children.push_back(res->columns); }
        if (select) { res->select = select->clone(); res->children.push_back(res->select); }
        if (watch) { res->watch = watch->clone(); res->children.push_back(res->watch); }
        if (table_function) { res->table_function = table_function->clone(); res->children.push_back(res->table_function); }
        if (settings_ast) { res->settings_ast = settings_ast->clone(); res->children.push_back(res->settings_ast); }

        return res;
    }

protected:
    void formatImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const override;
};

}
