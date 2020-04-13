#include "canvas.hpp"
#include "../gui/window.hpp"

#include <gdiplus.h>

Canvas::Canvas(Window *w) : window(w), bitmap(w->getWidth(), w->getHeight()) {
    w->addHandler(MessageHandler::onPaint([this](Window *w, WindowMessage) {
        HWND windowHandle = w->getWindowHandle();
        deviceContext = BeginPaint(windowHandle, &paintStruct);

        Gdiplus::Graphics graphics(deviceContext);
        onDraw(&graphics);

        EndPaint(windowHandle, &paintStruct);
    }));
}

void Canvas::addOnDrawListener(std::function<void(Gdiplus::Graphics *)> &&onDrawListener) {
    onDraw = onDrawListener != nullptr ? onDrawListener : [](Gdiplus::Graphics *) {};
}

void Canvas::removeOnDrawListener() {
    onDraw = [](Gdiplus::Graphics *) {};
}
