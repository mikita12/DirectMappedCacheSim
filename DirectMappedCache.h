#ifndef DIRECT_MAPPED_CACHE_H
#define DIRECT_MAPPED_CACHE_H

#include <cstdint>
#include <vector>

// Wynik dostępu do pamięci podręcznej
enum class AccessResult {
    Hit,
    Miss,
    MissConflict
};

// Linia cache
struct CacheLine {
    uint32_t tag;
    bool valid = false;
};

// Rozłożenie adresu
struct Address {
    uint32_t raw;
    uint32_t offset;
    uint32_t index;
    uint32_t tag;
};

// Funkcja pomocnicza do obliczania szerokości bitów
uint32_t bit_width(uint32_t bit);

// Funkcja dekodująca adres na tag, index i offset
Address decode_address(uint32_t address, uint32_t cache_size, uint32_t cache_line_size, uint32_t address_width);

// Klasa symulująca pamięć podręczną direct-mapped
class DirectMappedCache {
private:
    uint32_t cache_size;
    uint32_t cache_line_size;
    uint32_t address_width;
    std::vector<CacheLine> cache;

public:
    DirectMappedCache(uint32_t c_size, uint32_t c_line_size, uint32_t addr_width);

    // Funkcja dostępu do cache: zwraca Hit, Miss lub MissConflict
    AccessResult access(uint32_t address);
};

#endif // DIRECT_MAPPED_CACHE_H
