#include "libtcod.hpp"
#include <optional>
#include <utility>
#include <cstdint>
#include <memory_resource>
#include <memory>
#include <iostream>

// Constexpr construction
// constexpr uint8_t makeByte(uint8_t highNibble, uint8_t lowNibble)
// {
//     return (((highNibble & 0xF) << 4) | ((lowNibble & 0xF) << 0));
// }

// // Constexpr high nibble extraction
// constexpr uint8_t getHighNibble(uint8_t byte)
// {
//     return ((byte >> 4) & 0xF);
// }

// // Constexpr low nibble extraction
// constexpr uint8_t getLowNibble(uint8_t byte)
// {
//     return ((byte >> 0) & 0xF);
// }


// class SevenSegmentDisplay {
// private:
//     using Pinout = struct {
//         int  a;
//         int  b;
//         int  c; 
//         int  d; 
//         int  e; 
//         int  f;
//         int  g; 
//         int dt;
//     };
    
//     using State = uint8_t;

//     const SevenSegmentDisplay::Pinout pinout;
//     mutable SevenSegmentDisplay::State state;
// public:
//     SevenSegmentDisplay(SevenSegmentDisplay::Pinout pinout_) : pinout(pinout_) {};

//     void write(SevenSegmentDisplay::State state) { this->state = state; };
//     SevenSegmentDisplay::State read() { return this->state; };
// };

struct byte_t {
    uint8_t high : 4;
    uint8_t low  : 4;
};

struct ByteResource {

    ByteResource() {
        std::allocator<byte_t> alloc;
        uint8_t *res = reinterpret_cast<uint8_t *>(alloc.allocate(1));
    };
};

int main() {
    
    std::allocator<byte_t> alloc;
    auto *res =(alloc.allocate(1));

    res[0] = byte_t { .high = 2, .low = 0 };
    std::cout << static_cast<int>(*reinterpret_cast<uint8_t *>(res));

    return 0;
}