#pragma once

#include <Core/Types.h>

namespace DB
{

class Location
{
public:
    Location() = default;
    Location(UInt64 line, UInt64 column, UInt64 byte);

    inline UInt64 getLine() const { return line; }
    inline UInt64 getColumn() const { return column; }
    inline UInt64 getByte() const { return byte; }

    operator bool() const;
    bool operator<(const Location & other) const;

private:
    static constexpr UInt64 INVALID_VALUE = 0u;

    const UInt64 line = INVALID_VALUE;
    const UInt64 column = INVALID_VALUE;
    const UInt64 byte = INVALID_VALUE;
};

class LocationRange
{
public:
    LocationRange(const Location & begin, const Location & end);
    // The end is exclusive, i.e. [begin, end)

    const Location & begin() const { return begin_; }
    const Location & end() const { return end_; }

private:
    const Location begin_, end_;
};

}
