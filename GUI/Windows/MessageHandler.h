#pragma once

#include <windows.h>

class MessageHandler {
    UINT messageCode{0};
    void (*handle)(HWND, UINT, WPARAM, LPARAM);

public:
    MessageHandler(UINT msg, void (*handle)(HWND, UINT, WPARAM, LPARAM)) : messageCode(msg), handle(handle) {}

    void handleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        handle(hwnd, msg, wparam, lparam);
    }

    UINT getMessageCode() {
        return messageCode;
    }
};
