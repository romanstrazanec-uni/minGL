#ifndef MINGL_WINDOW_MESSAGE_INCLUDED
#define MINGL_WINDOW_MESSAGE_INCLUDED

#include <minwindef.h>
#include <winuser.h>
#include <w32api/windowsx.h>

class WindowMessage {
    UINT messageCode{0};
    WPARAM wparam{0};
    LPARAM lparam{0};

public:
    WindowMessage() = default;
    WindowMessage(const WindowMessage &) = default;
    WindowMessage(UINT code) : messageCode(code) {}
    WindowMessage(UINT code, WPARAM wparam, LPARAM lparam) : messageCode(code), wparam(wparam), lparam(lparam) {}

    WPARAM getWparam() const { return wparam; }
    LPARAM getLparam() const { return lparam; }
    UINT getMsg() const { return messageCode; }

    POINT getMousePosition() const {
        if (messageCode == WM_MOUSEMOVE) return {GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)};
    }

    /* UINT code comparators */

    // todo: operator in

    friend bool operator==(const WindowMessage &msg, UINT code) { return msg.messageCode == code; }
    friend bool operator!=(const WindowMessage &msg, UINT code) { return !(msg == code); }
    friend bool operator==(UINT code, const WindowMessage &msg) { return msg == code; }
    friend bool operator!=(UINT code, const WindowMessage &msg) { return msg != code; }

    /* WindowMessage comparators */
    friend bool operator==(const WindowMessage &msg1, const WindowMessage &msg2) {
        return msg1.messageCode == msg2.messageCode;
    }
    friend bool operator!=(const WindowMessage &msg1, const WindowMessage &msg2) {
        return !(msg1 == msg2);
    }

    /* Static Constructors */
    static WindowMessage onCreate() { return {WM_CREATE}; }
    static WindowMessage onPaint() { return {WM_PAINT}; }
    static WindowMessage onClose() { return {WM_CLOSE}; }
    static WindowMessage onMouseMove() { return {WM_MOUSEMOVE}; }
    static WindowMessage onLeftMouseButtonDown() { return {WM_LBUTTONDOWN}; }
    static WindowMessage onLeftMouseButtonUp() { return {WM_LBUTTONUP}; }
    static WindowMessage onMiddleMouseButtonDown() { return {WM_MBUTTONDOWN}; }
    static WindowMessage onMiddleMouseButtonUp() { return {WM_MBUTTONUP}; }
    static WindowMessage onRightMouseButtonDown() { return {WM_RBUTTONDOWN}; }
    static WindowMessage onRightMouseButtonUp() { return {WM_RBUTTONUP}; }
};

#endif
