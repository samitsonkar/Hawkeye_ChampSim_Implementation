#include "optgen.h"

OPTgen::OPTgen(std::size_t sets,std::size_t ways,std::size_t history)
    : ways_(ways),window_(ways*history),occupancy_(sets,std::vector<int>(ways*history,0)),previous_(sets),clocks_(sets,0)
{
}

bool OPTgen::access(std::size_t set,uint64_t block)
{
    uint64_t now=clocks_[set]++;
    auto& seen=previous_[set];
    auto& usage=occupancy_[set];

    usage[now%window_]=0;

    auto found=seen.find(block);

    if(found==seen.end()){
        seen.emplace(block,now);
        return false;
    }

    uint64_t old=found->second;
    found->second=now;

    if(now-old>=window_)
        return false;

    for(uint64_t pos=old;pos<now;++pos){
        if(usage[pos%window_]>=static_cast<int>(ways_))
            return false;
    }

    for(uint64_t pos=old;pos<now;++pos)
        ++usage[pos%window_];

    return true;
}