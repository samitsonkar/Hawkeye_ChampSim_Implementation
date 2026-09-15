#include "rrip.h"

#include <algorithm>

namespace {
constexpr int MAX_VALUE=7;
constexpr int INSERTION_LIMIT=6;
}

void update_rrpv(std::vector<int>& state,std::size_t way,Classification classification,bool hit)
{
    if(way>=state.size())
        return;
    
    if(classification==Classification::CACHE_AVERSE){
        state[way]=MAX_VALUE;
        return;
    }
    if(hit){
        state[way]=0;
        return;
    }
    for(std::size_t pos=0;pos<state.size();++pos){
        if(pos!=way&&state[pos]<INSERTION_LIMIT)
            ++state[pos];
    }

    state[way]=0;
}

std::size_t find_victim(std::vector<int>& state)
{
    if(state.empty())
        return 0;

    for(;;){
        const auto candidate=std::find(state.begin(),state.end(),MAX_VALUE);
        if(candidate!=state.end())
            return static_cast<std::size_t>(std::distance(state.begin(),candidate));
        for(auto& value:state)
            value=std::min(value+1,MAX_VALUE);
    }
}