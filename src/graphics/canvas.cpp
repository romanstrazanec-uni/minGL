#include "canvas.hpp"
#include "../gui/window.hpp"

#include <fstream>

#pragma pack(2)
struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    /** Set file size. */
    int32_t fileSize{0};
    int32_t reserved{0};
    /** Set data offset. */
    int32_t dataOffset{0};
};

#pragma pack(2)
struct BitmapInfoHeader {
    int32_t headerSize{40};
    /** Set width. */
    int32_t width{0};
    /** Set height. */
    int32_t height{0};
    int16_t planes{1};
    int16_t bitsPerPixel{24};
    int32_t compression{0};
    int32_t dataSize{0};
    int32_t horizontalResolution{2400};
    int32_t verticalResolution{2400};
    int32_t colors{0};
    int32_t importantColors{0};
};

const size_t fileHeaderSize = sizeof(BitmapFileHeader);
const size_t infoHeaderSize = sizeof(BitmapInfoHeader);
const size_t dataOffset = fileHeaderSize + infoHeaderSize;

Canvas::Canvas(Window *w) : window(w), width(w->getWidth()), height(w->getHeight()),
                            data(new uint8_t[dataOffset + w->getWidth() * w->getHeight() * 3]{}) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.dataOffset = dataOffset;
    fileHeader.fileSize = dataOffset + width * height * 3;

    infoHeader.width = width;
    infoHeader.height = height;

    uint8_t *pData = data.get();
    memcpy(pData, (uint8_t *) &fileHeader, fileHeaderSize);
    memcpy(pData + fileHeaderSize, (uint8_t *) &infoHeader, infoHeaderSize);

    w->addHandler(MessageHandler::onPaint([this](Window *w, WindowMessage) {
        HWND windowHandle = w->getWindowHandle();

        PAINTSTRUCT paintStruct;
        Gdiplus::Graphics graphics{BeginPaint(windowHandle, &paintStruct)};

        Gdiplus::Bitmap bitmap(width, height, width * 3, PixelFormat24bppRGB, data.get());
        graphics.DrawImage(&bitmap, 0, 0);

        onDraw(&graphics);

        EndPaint(windowHandle, &paintStruct);
    }));
}

Canvas::~Canvas() = default;

void Canvas::addOnDrawListener(std::function<void(Gdiplus::Graphics *)> &&onDrawListener) {
    onDraw = onDrawListener != nullptr ? onDrawListener : [](Gdiplus::Graphics *) {};
}

void Canvas::removeOnDrawListener() {
    onDraw = [](Gdiplus::Graphics *) {};
}

void Canvas::setPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pData = data.get();

    pData += dataOffset + (y * 3) * width + (x * 3);

    pData[0] = blue;
    pData[1] = green;
    pData[2] = red;
}

bool Canvas::write(const char *filename) const {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if (!file) return false;

    file.write((char *) data.get(), dataOffset + width * height * 3);

    file.close();
    return !!file;
}

uint8_t *Canvas::getData() const {
    return data.get();
}

uint8_t *Canvas::getPixels() const {
    return data.get() + dataOffset;
}
