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

    /* Static constructors */

    static MessageHandler onCreate(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onCreate(), handle};
    }

    static MessageHandler onPaint(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onPaint(), handle};
    }

    static MessageHandler onClose(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onClose(), handle};
    }

    static MessageHandler onMouseMove(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onMouseMove(), handle};
    }

    static MessageHandler onLeftMouseButtonDown(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onLeftMouseButtonDown(), handle};
    }

    static MessageHandler onLeftMouseButtonUp(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onLeftMouseButtonUp(), handle};
    }

    static MessageHandler onMiddleMouseButtonDown(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onMiddleMouseButtonDown(), handle};
    }

    static MessageHandler onMiddleMouseButtonUp(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onMiddleMouseButtonUp(), handle};
    }

    static MessageHandler onRightMouseButtonDown(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onRightMouseButtonDown(), handle};
    }

    static MessageHandler onRightMouseButtonUp(void (*handle)(Window *, WindowMessage)) {
        return {WindowMessage::onRightMouseButtonUp(), handle};
    }
};

#endif
