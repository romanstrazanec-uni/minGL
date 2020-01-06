#include "canvas.hpp"
#include "../gui/window.hpp"

#include <gdiplus.h>

Canvas::Canvas(Window *w) : window(w), pixelsSize(w->getWidth() * w->getHeight() * 3), pixels(new UINT8[pixelsSize]{}) {
    w->addHandler(MessageHandler::onPaint([this](Window *w, WindowMessage) {
        HWND windowHandle = w->getWindowHandle();
        deviceContext = BeginPaint(windowHandle, &paintStruct);

        Gdiplus::Graphics graphics(deviceContext);

        UINT8 *pPixel = pixels.get();
        if (updated)
            for (UINT iPixel = 0; iPixel < pixelsSize; iPixel += 3) {
                Gdiplus::SolidBrush brush(Gdiplus::Color(255, pPixel[iPixel], pPixel[iPixel + 1], pPixel[iPixel + 2]));
                UINT pos = iPixel / 3;
                graphics.FillRectangle(&brush, pos % w->getWidth(), pos / w->getWidth(), 1, 1);
            }
        updated = false;

        EndPaint(windowHandle, &paintStruct);
    }));
}

void Canvas::setPixel(UINT16 x, UINT16 y, UINT8 red, UINT8 green, UINT8 blue) {
    UINT8 *pPixel = pixels.get();

    pPixel += (y * 3) * window->getWidth() + (x * 3);

    pPixel[0] = red;
    pPixel[1] = green;
    pPixel[2] = blue;
    updated = true;
}
