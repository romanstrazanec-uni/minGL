#include <fstream>
#include <cstring>
#include "bitmap.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-pack"

#include "bitmap_file_header.h"

#pragma clang diagnostic pop

#include "bitmap_info_header.h"

const size_t fileHeaderSize = sizeof(BitmapFileHeader);
const size_t infoHeaderSize = sizeof(BitmapInfoHeader);
const size_t dataOffset = fileHeaderSize + infoHeaderSize;

BitMap::BitMap(uint32_t width, uint32_t height) : width(width), height(height),
                                                  data(new uint8_t[dataOffset + width * height * 3]{}) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.dataOffset = dataOffset;
    fileHeader.fileSize = dataOffset + width * height * 3;

    infoHeader.width = width;
    infoHeader.height = height;

    uint8_t *pData = data.get();
    memcpy(pData, (uint8_t *) &fileHeader, fileHeaderSize);
    memcpy(pData + fileHeaderSize, (uint8_t *) &infoHeader, infoHeaderSize);
}

void BitMap::setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pData = data.get();

    pData += dataOffset + (y * 3) * width + (x * 3);

    pData[0] = blue;
    pData[1] = green;
    pData[2] = red;
}

bool BitMap::write(const char *filename) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if (!file) return false;

    file.write((char *) data.get(), dataOffset + width * height * 3);

    file.close();
    return !!file;
}

uint8_t *BitMap::getData() {
    return data.get();
}

BitMap::~BitMap() = default;
