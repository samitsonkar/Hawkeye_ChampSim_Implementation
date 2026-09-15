#ifndef OPTGEN_H
#define OPTGEN_H

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

class OPTgen {
public:
    OPTgen(std::size_t sets, std::size_t ways, std::size_t history = 8);

    bool access(std::size_t set, uint64_t block);

private:
    using TimestampMap = std::unordered_map<uint64_t, uint64_t>;

    std::size_t ways_;
    std::size_t window_;
    std::vector<std::vector<int>> occupancy_;
    std::vector<TimestampMap> previous_;
    std::vector<uint64_t> clocks_;
};

#endif