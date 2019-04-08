#include "Window.h"

LRESULT Window::handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) {
    for(MessageHandler *msghandler : messageHandlers) msghandler->handleMessage(msg, wparam, lparam);
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(getWindowHandle(), &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(getWindowHandle(), &ps);
        }
            return 0;
        case WM_CLOSE:
            if (MessageBox(getWindowHandle(), "Really quit?", "My application", MB_OKCANCEL) == IDOK)
                DestroyWindow(getWindowHandle());
            return 0;
        default:
            return DefWindowProc(getWindowHandle(), msg, wparam, lparam);
    }
}