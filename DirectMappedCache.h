#ifndef DIRECT_MAPPED_CACHE_H
#define DIRECT_MAPPED_CACHE_H

#include <cstdint>
#include <vector>

enum class AccessResult {
    Hit,
    Miss,
    MissConflict
};

struct CacheLine {
    uint32_t tag;
    bool valid = false;
};

struct Address {
    uint32_t raw;
    uint32_t offset;
    uint32_t index;
    uint32_t tag;
};

uint32_t bit_width(uint32_t bit);

Address decode_address(uint32_t address, uint32_t cache_size, uint32_t cache_line_size, uint32_t address_width);

class DirectMappedCache {
private:
    uint32_t cache_size;
    uint32_t cache_line_size;
    uint32_t address_width;
    std::vector<CacheLine> cache;

public:
    DirectMappedCache(uint32_t c_size, uint32_t c_line_size, uint32_t addr_width);

    AccessResult access(uint32_t address);
};

#endif
