#ifndef MINGL_MESSAGE_HANDLER_INCLUDED
#define MINGL_MESSAGE_HANDLER_INCLUDED

#include "windowmessage.hpp"

#include <functional>
#include <utility>

class Window;

typedef std::function<void(Window *, const WindowMessage &)> Handle;

class MessageHandler {
    WindowMessage message{};
    Handle handle{};

public:
    MessageHandler() = default;

    MessageHandler(WindowMessage &&msg, Handle handle) // todo: rvalue handle?
            : message(msg), handle(std::move(handle)) {}

    void handleMessage(Window *window, const WindowMessage &msg) { // todo: should have perfect forwarding on msg
        if (message == msg) {
            message = msg;
            handle(window, message);
        }
    }

    const WindowMessage &getMessage() const { return message; }

    /* Static constructors */ // todo: rvalue refs?
    static MessageHandler onCreate(Handle handle) { return {WindowMessage::onCreate(), std::move(handle)}; }
    static MessageHandler onPaint(Handle handle) { return {WindowMessage::onPaint(), std::move(handle)}; }
    static MessageHandler onClose(Handle handle) { return {WindowMessage::onClose(), std::move(handle)}; }
    static MessageHandler onMouseMove(Handle handle) { return {WindowMessage::onMouseMove(), std::move(handle)}; }
    static MessageHandler onLeftMouseButtonDown(Handle handle) {
        return {WindowMessage::onLeftMouseButtonDown(), std::move(handle)};
    }
    static MessageHandler onLeftMouseButtonUp(Handle handle) {
        return {WindowMessage::onLeftMouseButtonUp(), std::move(handle)};
    }
    static MessageHandler onMiddleMouseButtonDown(Handle handle) {
        return {WindowMessage::onMiddleMouseButtonDown(), std::move(handle)};
    }
    static MessageHandler onMiddleMouseButtonUp(Handle handle) {
        return {WindowMessage::onMiddleMouseButtonUp(), std::move(handle)};
    }
    static MessageHandler onRightMouseButtonDown(Handle handle) {
        return {WindowMessage::onRightMouseButtonDown(), std::move(handle)};
    }
    static MessageHandler onRightMouseButtonUp(Handle handle) {
        return {WindowMessage::onRightMouseButtonUp(), std::move(handle)};
    }
};

#endif
