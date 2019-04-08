#pragma once

#include <vector>
#include "BaseWindow.h"
#include "MessageHandler.h"

class Window : public BaseWindow<Window> {
    std::vector<MessageHandler> messageHandlers;
public:
    LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override {
        HWND hwnd = getWindowHandle();
        for (MessageHandler msghandler : messageHandlers)
            if (msghandler.handleMessage(hwnd, msg, wparam, lparam)) return 0;
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    void addHandler(MessageHandler msgHandler) {
        messageHandlers.push_back(msgHandler);
    }
};