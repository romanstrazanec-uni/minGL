#ifndef MINGL_MESSAGE_HANDLER_HPP_INCLUDED
#define MINGL_MESSAGE_HANDLER_HPP_INCLUDED

#include "message.hpp"

class MessageHandler {
    Message message{};

    void (*handle)(HWND, Message){};

public:
    MessageHandler() = default;

    MessageHandler(Message msg, void (*handle)(HWND, Message)) : message(msg), handle(handle) {}

    void handleMessage(HWND hwnd, Message msg) {
        message = Message(message.getMsg(), msg.getWparam(), msg.getLparam());
        handle(hwnd, message);
    }

    Message getMessage() {
        return message;
    }
};

#endif
