//direct-mapped cache simulator
#include <cstdint>
#include <iostream>
#include <vector>
#include "DirectMappedCache.h"

uint32_t bit_width(uint32_t bit){

    uint32_t n=0;

    while(bit!=1){ 
        bit = bit>>1;
        n++;
    }

    return n;
}

Address decode_address(uint32_t address, uint32_t cache_size, uint32_t cache_line_size, uint32_t address_width){
    
    uint32_t offset_size = bit_width(cache_line_size)-1;
    uint32_t index_size = bit_width(cache_size/cache_line_size)-1;
    uint32_t tag_size = address_width - offset_size - index_size;

    uint32_t offset_mask = (1 << offset_size) - 1; //tag - index - offset 
    uint32_t index_mask = (1 << index_size) - 1;

    uint32_t offset = address & offset_mask;
    uint32_t index = (address >> offset_size) & index_mask;
    uint32_t tag = address >> (offset_size + index_size);

    Address params;
    params.raw = address;
    params.offset = offset;
    params.index = index;
    params.tag = tag; 

    return params;
}



DirectMappedCache::DirectMappedCache(uint32_t c_size, uint32_t c_line_size, uint32_t addr_width) : cache_size(c_size), cache_line_size(c_line_size), address_width(addr_width)
{
    cache.resize(cache_size/cache_line_size);
}


AccessResult DirectMappedCache::access(uint32_t address){
    Address addr = decode_address(address,cache_size,cache_line_size,address_width);

    if (cache[addr.index].valid == false){
        cache[addr.index].tag = addr.tag;
        cache[addr.index].valid = true;
        return AccessResult::Miss; //miss
    }else if (cache[addr.index].tag == addr.tag) return AccessResult::Hit; //hit
        else return AccessResult::MissConflict; //conflict miss
}