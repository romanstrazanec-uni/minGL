#ifndef MINGL_MESSAGE_HANDLER_INCLUDED
#define MINGL_MESSAGE_HANDLER_INCLUDED

#include <mingl/message.hpp>

class Window;

class MessageHandler {
    Message message{};

    void (*handle)(Window *, Message){};

public:
    MessageHandler() = default;

    MessageHandler(Message msg, void (*handle)(Window *, Message)) : message(msg), handle(handle) {}

    void handleMessage(Window *window, Message msg) {
        message = Message(message.getMsg(), msg.getWparam(), msg.getLparam());
        handle(window, message);
    }

    Message getMessage() {
        return message;
    }
};

#endif
