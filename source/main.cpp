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

/*

TODO: 
* Move away from std::allocator for better
    - References
    - Smart pointers, resource becomes a unique one, get functions return shared refs
    - Memory resources, somewhat obscure, could be better for regional stuff
*/
class ByteResource {
private:
    std::unique_ptr<byte_t> resource;
public:
    ByteResource(uint8_t high_, uint8_t low_) {
        this->resource = std::unique_ptr(new byte_t {.high=high_, .low=low_}); // persistent allocation
    };

    void set_low_nibble (uint8_t low)  { this->resource->low  = low;  }
    void set_high_nibble(uint8_t high) { this->resource->high = high; }

    // Force ceils nibble into high nibble to preserve information, use in-place swapping for bitfields
    uint8_t *get_low_nibble() {
        return reinterpret_cast<uint8_t *>(new byte_t { .high=resource->low, .low=0 }); //gets moved
    }

    // Force ceils nibble into high nibble to preserve information
    uint8_t *get_high_nibble() {
        return reinterpret_cast<uint8_t *>(new byte_t { .high=resource->high, .low=0 });
    }
    
    std::pair<std::unique_ptr<std::byte>, std::unique_ptr<std::byte>> nibble() {
        auto *res = resource.release();
        return std::make_pair(std::make_unique(res), std::make_unique(res));
    };
};

int main() {
    auto res = new ByteResource(0, 0);
    
    std::cout << static_cast<int>(*res->get_high_nibble()) << std::endl;
    std::cout << static_cast<int>(*res->get_low_nibble())  << std::endl;
    
    res->set_high_nibble(10);
    res->set_low_nibble(3);

    std::cout << static_cast<int>(*res->get_high_nibble()) << std::endl;
    std::cout << static_cast<int>(*res->get_low_nibble())  << std::endl;
    return 0;
}
