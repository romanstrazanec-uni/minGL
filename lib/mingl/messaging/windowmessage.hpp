#ifndef MINGL_MESSAGE_INCLUDED
#define MINGL_MESSAGE_INCLUDED

#include <windows.h>

class WindowMessage {
    UINT messageCode{0};
    WPARAM wparam{0};
    LPARAM lparam{0};

public:
    WindowMessage() = default;

    WindowMessage(const WindowMessage &) = default;

    WindowMessage(UINT code) : messageCode(code) {}

    WindowMessage(UINT code, WPARAM wparam, LPARAM lparam) : messageCode(code), wparam(wparam), lparam(lparam) {}

    inline WPARAM getWparam() const {
        return wparam;
    }

    inline LPARAM getLparam() const {
        return lparam;
    }

    inline friend bool operator==(const WindowMessage &msg, UINT code) {
        return msg.messageCode == code;
    }

    inline friend bool operator!=(const WindowMessage &msg, UINT code) {
        return !(msg == code);
    }

    inline friend bool operator==(UINT code, const WindowMessage &msg) {
        return msg == code;
    }

    inline friend bool operator!=(UINT code, const WindowMessage &msg) {
        return msg != code;
    }

    inline friend bool operator==(const WindowMessage &msg1, const WindowMessage &msg2) {
        return msg1.messageCode == msg2.messageCode;
    }

    inline friend bool operator!=(const WindowMessage &msg1, const WindowMessage &msg2) {
        return !(msg1 == msg2);
    }

    inline UINT getMsg() const {
        return messageCode;
    }

    inline static WindowMessage onCreate() {
        return {WM_CREATE};
    }

    inline static WindowMessage onPaint() {
        return {WM_PAINT};
    }

    inline static WindowMessage onClose() {
        return {WM_CLOSE};
    }

    inline static WindowMessage onMouseMove() {
        return {WM_MOUSEMOVE};
    }

    inline static WindowMessage onLeftMouseButtonDown() {
        return {WM_LBUTTONDOWN};
    }

    inline static WindowMessage onLeftMouseButtonUp() {
        return {WM_LBUTTONDOWN};
    }

    inline static WindowMessage onMiddleMouseButtonDown() {
        return {WM_LBUTTONDOWN};
    }

    inline static WindowMessage onMiddleMouseButtonUp() {
        return {WM_LBUTTONDOWN};
    }

    inline static WindowMessage onRightMouseButtonDown() {
        return {WM_LBUTTONDOWN};
    }

    inline static WindowMessage onRightMouseButtonUp() {
        return {WM_LBUTTONDOWN};
    }
};

#endif
