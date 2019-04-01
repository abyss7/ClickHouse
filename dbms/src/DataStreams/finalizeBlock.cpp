#include <DataStreams/finalizeBlock.h>
#include <DataTypes/DataTypeAggregateFunction.h>
#include <Columns/ColumnAggregateFunction.h>


namespace DB
{
    void finalizeBlock(Block & block)
    {
        for (size_t i = 0; i < block.columns(); ++i)
        {
            ColumnWithTypeAndName & current = block.getByPosition(i);
            const auto * unfinalized_type = current.type->as<DataTypeAggregateFunction>();

            if (unfinalized_type)
            {
                current.type = unfinalized_type->getReturnType();
                if (current.column)
                    current.column = current.column->as<ColumnAggregateFunction&>().convertToValues();
            }
        }
    }
}
