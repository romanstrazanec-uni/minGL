#ifndef MINGL_BITMAP_INCLUDED
#define MINGL_BITMAP_INCLUDED

#include <string>
#include <cstdint>
#include <memory>

class BitMap {
private:
    uint32_t width{0};
    uint32_t height{0};
    std::unique_ptr<uint8_t[]> data{nullptr};

public:
    BitMap(uint32_t width, uint32_t height);
    void setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
    bool write(const char *filename);
    uint8_t *getData();
    virtual ~BitMap();
};

#endif
