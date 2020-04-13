#ifndef MINGL_BITMAP_FILE_HEADER_INCLUDED
#define MINGL_BITMAP_FILE_HEADER_INCLUDED

#include <cstdint>

#pragma pack(2)
struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    /** Set file size. */
    int32_t fileSize{0};
    int32_t reserved{0};
    /** Set data offset. */
    int32_t dataOffset{0};
};

#endif
