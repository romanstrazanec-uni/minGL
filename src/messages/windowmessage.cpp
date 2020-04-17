#include "windowmessage.hpp"
#include <windowsx.h> // GET_X_Y_PARAM
#include <winuser.h> // WM message codes

WindowMessage::WindowMessage(const WindowMessage &) = default;
WindowMessage::WindowMessage(UINT code)
        : code(code) {}
WindowMessage::WindowMessage(UINT code, WPARAM wParam, LPARAM lParam)
        : code(code), wParam(wParam), lParam(lParam) {}

UINT WindowMessage::getCode() const { return code; }
WPARAM WindowMessage::getWparam() const { return wParam; }
LPARAM WindowMessage::getLparam() const { return lParam; }

POINT WindowMessage::getMousePosition() const {
    switch (code) {
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
        default:
            return {0, 0};
    }
}

bool operator==(const WindowMessage &msg, UINT c) { return msg.code == c; }
bool operator!=(const WindowMessage &msg, UINT c) { return !(msg == c); }
bool operator==(UINT c, const WindowMessage &msg) { return msg == c; }
bool operator!=(UINT c, const WindowMessage &msg) { return msg != c; }
bool operator==(const WindowMessage &msg1, const WindowMessage &msg2) { return msg1.code == msg2.code; }
bool operator!=(const WindowMessage &msg1, const WindowMessage &msg2) { return !(msg1 == msg2); }

WindowMessage WindowMessage::onCreate() { return {WM_CREATE}; }
WindowMessage WindowMessage::onPaint() { return {WM_PAINT}; }
WindowMessage WindowMessage::onClose() { return {WM_CLOSE}; }
WindowMessage WindowMessage::onMouseMove() { return {WM_MOUSEMOVE}; }
WindowMessage WindowMessage::onLeftMouseButtonDown() { return {WM_LBUTTONDOWN}; }
WindowMessage WindowMessage::onLeftMouseButtonUp() { return {WM_LBUTTONUP}; }
WindowMessage WindowMessage::onMiddleMouseButtonDown() { return {WM_MBUTTONDOWN}; }
WindowMessage WindowMessage::onMiddleMouseButtonUp() { return {WM_MBUTTONUP}; }
WindowMessage WindowMessage::onRightMouseButtonDown() { return {WM_RBUTTONDOWN}; }
WindowMessage WindowMessage::onRightMouseButtonUp() { return {WM_RBUTTONUP}; }
