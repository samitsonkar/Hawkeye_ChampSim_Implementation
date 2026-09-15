#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <cstddef>
#include <cstdint>
#include <vector>

class HawkeyePredictor {
public:
    HawkeyePredictor(std::size_t entries = 8192, int bits = 3);

    void train(uint64_t pc, bool opt_hit);
    bool predict(uint64_t pc) const;
    int get_counter(uint64_t pc) const;

private:
    std::size_t entry_count;
    int counter_max;
    std::vector<int> counters;

    std::size_t index(uint64_t pc) const;
};

#endif