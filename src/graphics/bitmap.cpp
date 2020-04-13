#include <fstream>
#include "bitmap.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-pack"

#include "bitmap_file_header.h"

#pragma clang diagnostic pop

#include "bitmap_info_header.h"

Bitmap::Bitmap(int width, int height) : width(width), height(height),
                                        pixels(new uint8_t[width * height * 3]{}) {}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pPixel = pixels.get();

    pPixel += (y * 3) * width + (x * 3);

    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;
}

bool Bitmap::write(const char *filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + width * height * 3;
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = width;
    infoHeader.height = height;

    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if (!file) return false;

    file.write((char *) &fileHeader, sizeof(fileHeader));
    file.write((char *) &infoHeader, sizeof(infoHeader));
    file.write((char *) pixels.get(), width * height * 3);

    file.close();
    return !!file;
}

Bitmap::~Bitmap() = default;
