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
    byte_t *resource;
public:
    ByteResource() {
        std::allocator<byte_t> alloc;
        this->resource = alloc.allocate(1);
    };

    void set_low_nibble(uint8_t low)   { this->resource->low  = low;  }
    void set_high_nibble(uint8_t high) { this->resource->high = high; }

    // Force ceils nibble into high nibble to preserve information
    uint8_t *get_low_nibble() {
        return reinterpret_cast<uint8_t *>(new byte_t { .high=resource->low, .low=0 });
    }

    // Force ceils nibble into high nibble to preserve information
    uint8_t *get_high_nibble() {
        return reinterpret_cast<uint8_t *>(new byte_t { .high=resource->high, .low=0 });
    }
};

int main() {
    auto res = new ByteResource();
    
    res->set_high_nibble(10);
    res->set_low_nibble(3);

    std::cout << static_cast<int>(*res->get_high_nibble()) << std::endl;
    std::cout << static_cast<int>(*res->get_low_nibble())  << std::endl;
    return 0;
}