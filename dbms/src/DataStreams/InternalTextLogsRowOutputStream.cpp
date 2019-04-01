#include "InternalTextLogsRowOutputStream.h"
#include <Core/Block.h>
#include <Interpreters/InternalTextLogsQueue.h>
#include <DataTypes/IDataType.h>
#include <Columns/ColumnsNumber.h>
#include <Columns/ColumnString.h>
#include <IO/WriteHelpers.h>


namespace DB
{

Block InternalTextLogsRowOutputStream::getHeader() const
{
    return InternalTextLogsQueue::getSampleBlock();
}

void InternalTextLogsRowOutputStream::write(const Block & block)
{
    const auto & array_event_time = block.getByName("event_time").column->as<ColumnUInt32>()->getData();
    const auto & array_microseconds = block.getByName("event_time_microseconds").column->as<ColumnUInt32>()->getData();

    const auto & column_host_name = block.getByName("host_name").column->as<ColumnString &>();
    const auto & column_query_id = block.getByName("query_id").column->as<ColumnString>();

    const auto & array_thread_number = block.getByName("thread_number").column->as<ColumnUInt32 &>().getData();
    const auto & array_priority = block.getByName("priority").column->as<ColumnInt8 &>().getData();
    const auto & column_source = block.getByName("source").column->as<ColumnString &>();
    const auto & column_text = block.getByName("text").column->as<ColumnString &>();

    for (size_t row_num = 0; row_num < block.rows(); ++row_num)
    {
        auto host_name = column_host_name.getDataAt(row_num);
        if (host_name.size)
        {
            writeCString("[", wb);
            writeString(host_name, wb);
            writeCString("] ", wb);
        }

        auto event_time = array_event_time[row_num];
        writeDateTimeText<'.', ':'>(event_time, wb);

        auto microseconds = array_microseconds[row_num];
        writeChar('.', wb);
        writeChar('0' + ((microseconds / 100000) % 10), wb);
        writeChar('0' + ((microseconds / 10000) % 10), wb);
        writeChar('0' + ((microseconds / 1000) % 10), wb);
        writeChar('0' + ((microseconds / 100) % 10), wb);
        writeChar('0' + ((microseconds / 10) % 10), wb);
        writeChar('0' + ((microseconds / 1) % 10), wb);

        auto query_id = column_query_id.getDataAt(row_num);
        if (query_id.size)
        {
            writeCString(" {", wb);
            writeString(query_id, wb);
            writeCString("}", wb);
        }

        UInt32 thread_number = array_thread_number[row_num];
        writeCString(" [ ", wb);
        writeIntText(thread_number, wb);
        writeCString(" ] <", wb);

        Int8 priority = array_priority[row_num];
        writeString(InternalTextLogsQueue::getPriorityName(priority), wb);
        writeCString("> ", wb);

        auto source = column_source.getDataAt(row_num);
        writeString(source, wb);
        writeCString(": ", wb);

        auto text = column_text.getDataAt(row_num);
        writeString(text, wb);

        writeChar('\n', wb);
    }
}

}
