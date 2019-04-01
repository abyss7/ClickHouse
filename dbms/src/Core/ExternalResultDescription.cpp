#include "ExternalResultDescription.h"
#include <DataTypes/DataTypeDate.h>
#include <DataTypes/DataTypeDateTime.h>
#include <DataTypes/DataTypeNullable.h>
#include <DataTypes/DataTypeString.h>
#include <DataTypes/DataTypeUUID.h>
#include <DataTypes/DataTypesNumber.h>
#include <ext/range.h>


namespace DB
{
namespace ErrorCodes
{
    extern const int UNKNOWN_TYPE;
}

void ExternalResultDescription::init(const Block & sample_block_)
{
    sample_block = sample_block_;

    types.reserve(sample_block.columns());

    for (auto & elem : sample_block)
    {
        /// If default value for column was not provided, use default from data type.
        if (elem.column->empty())
            elem.column = elem.type->createColumnConstWithDefaultValue(1)->convertToFullColumnIfConst();

        bool is_nullable = elem.type->isNullable();
        DataTypePtr type_not_nullable = removeNullable(elem.type);
        const IDataType * type = type_not_nullable.get();

        if (type->as<DataTypeUInt8>())
            types.emplace_back(ValueType::UInt8, is_nullable);
        else if (type->as<DataTypeUInt16>())
            types.emplace_back(ValueType::UInt16, is_nullable);
        else if (type->as<DataTypeUInt32>())
            types.emplace_back(ValueType::UInt32, is_nullable);
        else if (type->as<DataTypeUInt64>())
            types.emplace_back(ValueType::UInt64, is_nullable);
        else if (type->as<DataTypeInt8>())
            types.emplace_back(ValueType::Int8, is_nullable);
        else if (type->as<DataTypeInt16>())
            types.emplace_back(ValueType::Int16, is_nullable);
        else if (type->as<DataTypeInt32>())
            types.emplace_back(ValueType::Int32, is_nullable);
        else if (type->as<DataTypeInt64>())
            types.emplace_back(ValueType::Int64, is_nullable);
        else if (type->as<DataTypeFloat32>())
            types.emplace_back(ValueType::Float32, is_nullable);
        else if (type->as<DataTypeFloat64>())
            types.emplace_back(ValueType::Float64, is_nullable);
        else if (type->as<DataTypeString>())
            types.emplace_back(ValueType::String, is_nullable);
        else if (type->as<DataTypeDate>())
            types.emplace_back(ValueType::Date, is_nullable);
        else if (type->as<DataTypeDateTime>())
            types.emplace_back(ValueType::DateTime, is_nullable);
        else if (type->as<DataTypeUUID>())
            types.emplace_back(ValueType::UUID, is_nullable);
        else
            throw Exception{"Unsupported type " + type->getName(), ErrorCodes::UNKNOWN_TYPE};
    }
}

}
