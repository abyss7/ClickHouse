#include "src/IO/WriteBufferFromFileBase.h"

namespace DB
{

WriteBufferFromFileBase::WriteBufferFromFileBase(size_t buf_size, char * existing_memory, size_t alignment)
    : BufferWithOwnMemory<WriteBuffer>(buf_size, existing_memory, alignment)
{
}

}
