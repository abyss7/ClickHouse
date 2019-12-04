#pragma once
#include <Processors/ISource.h>


namespace DB
{

class NullSource : public ISource
{
public:
    explicit NullSource(Block header) : ISource(std::move(header)) {}
    String getName() const override { return "NullSource"; }

protected:
    std::optional<Chunk> generate() override { return {}; }
};

}
