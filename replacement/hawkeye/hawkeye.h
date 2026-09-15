#ifndef HAWKEYE_H
#define HAWKEYE_H
#include "cache.h"
#include "modules.h"
#include "optgen.h"
#include "predictor.h"
#include "rrip.h"
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>
struct hawkeye:public champsim::modules::replacement{
    OPTgen generator;
    HawkeyePredictor classifier;
    std::vector<std::vector<int>> line_state;
    std::vector<std::unordered_map<uint64_t,uint64_t>> pc_history;
    std::size_t block_shift;
    
    explicit hawkeye(CACHE* cache):replacement(cache),generator(cache->NUM_SET,cache->NUM_WAY,8),classifier(),line_state(cache->NUM_SET,std::vector<int>(cache->NUM_WAY,7)),pc_history(cache->NUM_SET),block_shift(static_cast<std::size_t>(cache->OFFSET_BITS)){}
    
    long find_victim(uint32_t triggering_cpu,uint64_t instr_id,long set,const champsim::cache_block* current_set,champsim::address ip,champsim::address full_addr,access_type type);
    
    void update_replacement_state(uint32_t triggering_cpu,long set,long way,champsim::address full_addr,champsim::address ip,champsim::address victim_addr,access_type type,bool hit);
    
    void replacement_cache_fill(uint32_t triggering_cpu,long set,long way,champsim::address full_addr,champsim::address ip,champsim::address victim_addr,access_type type);

    private:
    uint64_t to_block(champsim::address address)const;
};
#endif