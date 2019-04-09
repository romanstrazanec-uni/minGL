#pragma once

#include <map>
#include "BaseWindow.h"
#include "MessageHandler.h"

class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers;
public:
    LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override {
        if(messageHandlers.count(msg) == 0) return DefWindowProc(getWindowHandle(), msg, wparam, lparam);
        messageHandlers[msg].handleMessage(getWindowHandle(), msg, wparam, lparam);
        return 0;
    }

    void addHandler(MessageHandler msgHandler) {
        messageHandlers[msgHandler.getMessageCode()] = msgHandler;
    }
};