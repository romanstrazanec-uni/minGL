#pragma once
#include <vector>
#include "BaseWindow.h"
#include "../MessageHandlers/MessageHandler.h"

class Window: public BaseWindow<Window> {
    std::vector<MessageHandler *> messageHandlers;
public:
    LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override;
};