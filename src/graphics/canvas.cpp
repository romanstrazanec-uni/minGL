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

static const size_t fileHeaderSize = sizeof(BitmapFileHeader);
static const size_t infoHeaderSize = sizeof(BitmapInfoHeader);
static const size_t dataOffset = fileHeaderSize + infoHeaderSize;

Canvas::Canvas(Window *w)
        : window(w),
          width(w->getWidth()),
          height(w->getHeight()),
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

    drawArea(0, 0, width, height, RGBColor(255, 255, 255));

    w->addHandler(WindowMessage::onPaint(), [this](const WindowMessage &) {
        HWND windowHandle = window->getWindowHandle();

        PAINTSTRUCT paintStruct;
        Gdiplus::Graphics graphics{BeginPaint(windowHandle, &paintStruct)};

        Gdiplus::Bitmap bitmap(
                width,
                height,
                width * 3,
                PixelFormat24bppRGB,
                data.get()
        );
        graphics.DrawImage(&bitmap, 0, 0);

        onDraw(&graphics);

        EndPaint(windowHandle, &paintStruct);
    });
}

Canvas::~Canvas() = default;

void Canvas::addOnDrawListener(OnDrawHandle &&onDrawListener) {
    onDraw = onDrawListener != nullptr ? onDrawListener : [](Gdiplus::Graphics *) {};
}
void Canvas::removeOnDrawListener() {
    onDraw = [](Gdiplus::Graphics *) {};
}

void Canvas::setPixel(UINT16 x, UINT16 y, const RGBColor &color) {
    uint8_t *pData = data.get() + dataOffset + y * 3 * width + x * 3;
    pData[0] = color.blue;
    pData[1] = color.green;
    pData[2] = color.red;
}

void Canvas::drawArea(UINT16 x, UINT16 y, UINT16 w, UINT16 h, const RGBColor &color) {
    uint8_t *pData = data.get() + dataOffset + y * 3 * width + x * 3;

    for (y = 0; y < h; ++y)
        for (x = 0; x < w; ++x) {
            pData[x * 3 + y * 3 * width] = color.blue;
            pData[1 + x * 3 + y * 3 * width] = color.green;
            pData[2 + x * 3 + y * 3 * width] = color.red;
        }
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
