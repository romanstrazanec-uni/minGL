#ifndef BITMAP_INCLUDED
#define BITMAP_INCLUDED

#include <string>
#include <cstdint>
#include <memory>

class Bitmap {
private:
    int width{0};
    int height{0};
    std::unique_ptr<uint8_t[]> pixels{nullptr};

public:
    Bitmap(int width, int height);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    bool write(const char *filename);
    virtual ~Bitmap();
};

#endif
