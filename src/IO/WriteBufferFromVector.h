#pragma once

#include <vector>

#include "src/IO/WriteBuffer.h"


namespace DB
{

namespace ErrorCodes
{
    extern const int CANNOT_WRITE_AFTER_END_OF_BUFFER;
}

/** Writes data to existing std::vector or similar type. When not enough space, it doubles vector size.
  *
  * In destructor, vector is cutted to the size of written data.
  * You can call to 'finish' to resize earlier.
  *
  * The vector should live until this object is destroyed or until the 'finish' method is called.
  */
template <typename VectorType>
class WriteBufferFromVector : public WriteBuffer
{
private:
    VectorType & vector;
    bool is_finished = false;

    static constexpr size_t initial_size = 32;
    static constexpr size_t size_multiplier = 2;

    void nextImpl() override
    {
        if (is_finished)
            throw Exception("WriteBufferFromVector is finished", ErrorCodes::CANNOT_WRITE_AFTER_END_OF_BUFFER);

        size_t old_size = vector.size();
        vector.resize(old_size * size_multiplier);
        internal_buffer = Buffer(reinterpret_cast<Position>(vector.data() + old_size), reinterpret_cast<Position>(vector.data() + vector.size()));
        working_buffer = internal_buffer;
    }

public:
    WriteBufferFromVector(VectorType & vector_)
        : WriteBuffer(reinterpret_cast<Position>(vector_.data()), vector_.size()), vector(vector_)
    {
        if (vector.empty())
        {
            vector.resize(initial_size);
            set(reinterpret_cast<Position>(vector.data()), vector.size());
        }
    }

    /// Append to vector instead of rewrite.
    struct AppendModeTag {};
    WriteBufferFromVector(VectorType & vector_, AppendModeTag)
        : WriteBuffer(nullptr, 0), vector(vector_)
    {
        size_t old_size = vector.size();
        size_t size = (old_size < initial_size) ? initial_size
                                                : ((old_size < vector.capacity()) ? vector.capacity()
                                                                                  : vector.capacity() * size_multiplier);
        vector.resize(size);
        set(reinterpret_cast<Position>(vector.data() + old_size), (size - old_size) * sizeof(typename VectorType::value_type));
    }

    void finalize() override final
    {
        if (is_finished)
            return;
        is_finished = true;
        vector.resize(
            ((position() - reinterpret_cast<Position>(vector.data()))
                + sizeof(typename VectorType::value_type) - 1)  /// Align up.
            / sizeof(typename VectorType::value_type));

        /// Prevent further writes.
        set(nullptr, 0);
    }

    bool isFinished() const { return is_finished; }

    void restart()
    {
        set(reinterpret_cast<Position>(vector.data()), vector.size());
        is_finished = false;
    }

    ~WriteBufferFromVector() override
    {
        try
        {
            finalize();
        }
        catch (...)
        {
            tryLogCurrentException(__PRETTY_FUNCTION__);
        }
    }
};

}
