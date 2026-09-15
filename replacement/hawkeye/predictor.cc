#include "predictor.h"

HawkeyePredictor::HawkeyePredictor(std::size_t entries,int bits)
    : entry_count(entries),counter_max((1<<bits)-1),counters(entries,1<<(bits-1))
{
}

std::size_t HawkeyePredictor::index(uint64_t pc)const
{
    uint64_t mixed=pc^(pc>>12);
    return mixed&(entry_count-1);
}

void HawkeyePredictor::train(uint64_t pc,bool opt_hit)
{
    int& value=counters[index(pc)];

    if(opt_hit){
        value=std::min(counter_max,value+1);
    }else{
        value=std::max(0,value-1);
    }
}

bool HawkeyePredictor::predict(uint64_t pc)const
{
    return counters[index(pc)]>=(counter_max+1)/2;
}

int HawkeyePredictor::get_counter(uint64_t pc)const
{
    return counters[index(pc)];
}