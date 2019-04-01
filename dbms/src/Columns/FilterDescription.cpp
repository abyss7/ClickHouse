#include <Columns/FilterDescription.h>
#include <Columns/ColumnsNumber.h>
#include <Columns/ColumnNullable.h>
#include <Columns/ColumnConst.h>
#include <Core/ColumnWithTypeAndName.h>


namespace DB
{

namespace ErrorCodes
{
    extern const int ILLEGAL_TYPE_OF_COLUMN_FOR_FILTER;
}


ConstantFilterDescription::ConstantFilterDescription(const IColumn & column)
{
    if (column.onlyNull())
    {
        always_false = true;
        return;
    }

    if (column.isColumnConst())
    {
        const ColumnConst & column_const = static_cast<const ColumnConst &>(column);
        ColumnPtr column_nested = column_const.getDataColumnPtr()->convertToFullColumnIfLowCardinality();

        if (!column_nested->as<ColumnUInt8>())
        {
            const auto * column_nested_nullable = column_nested->as<ColumnNullable>();
            if (!column_nested_nullable || !column_nested_nullable->getNestedColumn().as<ColumnUInt8>())
            {
                throw Exception("Illegal type " + column_nested->getName() + " of column for constant filter. Must be UInt8 or Nullable(UInt8).",
                                ErrorCodes::ILLEGAL_TYPE_OF_COLUMN_FOR_FILTER);
            }
        }

        if (column_const.getValue<UInt64>())
            always_true = true;
        else
            always_false = true;
        return;
    }
}


FilterDescription::FilterDescription(const IColumn & column_)
{
    if (column_.lowCardinality())
        data_holder = column_.convertToFullColumnIfLowCardinality();

    const auto & column = data_holder ? *data_holder : column_;

    if (const auto * concrete_column = column.as<ColumnUInt8>())
    {
        data = &concrete_column->getData();
        return;
    }

    if (const auto * nullable_column = column.as<ColumnNullable>())
    {
        ColumnPtr nested_column = nullable_column->getNestedColumnPtr();
        MutableColumnPtr mutable_holder = (*std::move(nested_column)).mutate();

        auto * concrete_column = mutable_holder->as<ColumnUInt8>();
        if (!concrete_column)
            throw Exception("Illegal type " + column.getName() + " of column for filter. Must be UInt8 or Nullable(UInt8).",
                ErrorCodes::ILLEGAL_TYPE_OF_COLUMN_FOR_FILTER);

        const NullMap & null_map = nullable_column->getNullMapData();
        IColumn::Filter & res = concrete_column->getData();

        size_t size = res.size();
        for (size_t i = 0; i < size; ++i)
            res[i] = res[i] && !null_map[i];

        data = &res;
        data_holder = std::move(mutable_holder);
        return;
    }

    throw Exception("Illegal type " + column.getName() + " of column for filter. Must be UInt8 or Nullable(UInt8) or Const variants of them.",
        ErrorCodes::ILLEGAL_TYPE_OF_COLUMN_FOR_FILTER);
}


void checkColumnCanBeUsedAsFilter(const ColumnWithTypeAndName & column_elem)
{
    ConstantFilterDescription const_filter;
    if (column_elem.column)
        const_filter = ConstantFilterDescription(*column_elem.column);

    if (!const_filter.always_false && !const_filter.always_true)
    {
        auto column = column_elem.column ? column_elem.column : column_elem.type->createColumn();
        FilterDescription filter(*column);
    }
}

}
