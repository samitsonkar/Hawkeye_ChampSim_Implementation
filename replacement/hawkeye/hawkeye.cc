#include "hawkeye.h"

uint64_t hawkeye::to_block(champsim::address address)const
{
    return address.to<uint64_t>()>>block_shift;
}

long hawkeye::find_victim(uint32_t,uint64_t,long set,const champsim::cache_block*,champsim::address,champsim::address,access_type)
{
    return static_cast<long>(::find_victim(line_state[static_cast<std::size_t>(set)]));
}

void hawkeye::replacement_cache_fill(uint32_t,long set,long way,champsim::address full_addr,champsim::address ip,champsim::address,access_type)
{
    struct Access{
        std::size_t set;
        std::size_t way;
        uint64_t block;
        uint64_t pc;
    };

    Access a{
        static_cast<std::size_t>(set),
        static_cast<std::size_t>(way),
        to_block(full_addr),
        ip.to<uint64_t>()
    };

    auto cls=classifier.predict(a.pc)?Classification::CACHE_FRIENDLY:Classification::CACHE_AVERSE;
    bool opt_hit=generator.access(a.set,a.block);
    auto it=pc_history[a.set].find(a.block);

    if(it!=pc_history[a.set].end())
        classifier.train(it->second,opt_hit);

    pc_history[a.set][a.block]=a.pc;
    ::update_rrpv(line_state[a.set],a.way,cls,false);
}

void hawkeye::update_replacement_state(uint32_t,long set,long way,champsim::address full_addr,champsim::address ip,champsim::address,access_type,bool hit)
{
    if(!hit)
        return;

    struct Access{
        std::size_t set;
        std::size_t way;
        uint64_t block;
        uint64_t pc;
    };

    Access a{
        static_cast<std::size_t>(set),
        static_cast<std::size_t>(way),
        to_block(full_addr),
        ip.to<uint64_t>()
    };

    auto cls=classifier.predict(a.pc)?Classification::CACHE_FRIENDLY:Classification::CACHE_AVERSE;
    bool opt_hit=generator.access(a.set,a.block);
    auto it=pc_history[a.set].find(a.block);

    if(it!=pc_history[a.set].end())
        classifier.train(it->second,opt_hit);

    pc_history[a.set][a.block]=a.pc;
    ::update_rrpv(line_state[a.set],a.way,cls,true);
}