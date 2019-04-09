#pragma once

#include <map>
#include "BaseWindow.h"
#include "MessageHandler.h"

class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers;
public:
    LRESULT handleMessage(Message msg) override {
        if(messageHandlers.count(msg.getMsg()) == 0)
            return DefWindowProc(getWindowHandle(), msg.getMsg(), msg.getWparam(), msg.getLparam());
        messageHandlers[msg.getMsg()].handleMessage(getWindowHandle(), msg);
        return 0;
    }

    void addHandler(MessageHandler msgHandler) {
        messageHandlers[msgHandler.getMessage().getMsg()] = msgHandler;
    }
};