#pragma once

#include <Parsers/New/AST/Query.h>


namespace DB::AST
{

class SelectUnionQuery : public Query
{
    public:
        void appendSelect(PtrTo<SelectStmt> stmt);

        ASTPtr convertToOld() const override;
};

}
