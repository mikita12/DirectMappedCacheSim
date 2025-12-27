#include <cstdint>
#include <iostream>
#include <vector>
#include "DirectMappedCache.h"

int main() {

    DirectMappedCache cache(
        4096, // cache_size
        64,   // cache_line_size
        32    // address_width
    );

    uint32_t addr1 = 0x00000000;
    uint32_t addr2 = 0x00000040; // +64B -> inna linia
    uint32_t addr3 = 0x00000000; // ten sam co addr1

    AccessResult r1 = cache.access(addr1);
    AccessResult r2 = cache.access(addr2);
    AccessResult r3 = cache.access(addr3);

    std::cout << "addr1: " << static_cast<int>(r1) << "\n";
    std::cout << "addr2: " << static_cast<int>(r2) << "\n";
    std::cout << "addr3: " << static_cast<int>(r3) << "\n";

    return 0;
}
