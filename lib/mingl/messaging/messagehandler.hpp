#ifndef MINGL_MESSAGE_HANDLER_INCLUDED
#define MINGL_MESSAGE_HANDLER_INCLUDED

#include <mingl/messaging/windowmessage.hpp>

class Window;

class MessageHandler {
    WindowMessage message{};

    void (*handle)(Window *, WindowMessage){};

public:
    MessageHandler() = default;

    MessageHandler(WindowMessage msg, void (*handle)(Window *, WindowMessage)) : message(msg), handle(handle) {}

    void handleMessage(Window *window, WindowMessage msg) {
        if (message == msg) {
            message = msg;
            handle(window, message);
        }
    }

    const WindowMessage &getMessage() const {
        return message;
    }
};

#endif
