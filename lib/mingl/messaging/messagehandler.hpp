#ifndef MINGL_MESSAGE_HANDLER_INCLUDED
#define MINGL_MESSAGE_HANDLER_INCLUDED

#include <functional>
#include <utility>

#include <mingl/messaging/windowmessage.hpp>

class Window;

class MessageHandler {
    WindowMessage message{};
    std::function<void(Window *, const WindowMessage &)> handle{};

public:
    MessageHandler() = default;

    MessageHandler(WindowMessage &&msg,
                   std::function<void(Window *, const WindowMessage &)> handle) // todo: rvalue handle?
            : message(msg), handle(std::move(handle)) {}

    void handleMessage(Window *window, const WindowMessage &msg) { // todo: should have perfect forwarding on msg
        if (message == msg) {
            message = msg;
            handle(window, message);
        }
    }

    const WindowMessage &getMessage() const {
        return message;
    }

    /* Static constructors */ // todo: rvalue refs?

    static MessageHandler onCreate(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onCreate(), std::move(handle)};
    }

    static MessageHandler onPaint(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onPaint(), std::move(handle)};
    }

    static MessageHandler onClose(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onClose(), std::move(handle)};
    }

    static MessageHandler onMouseMove(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onMouseMove(), std::move(handle)};
    }

    static MessageHandler onLeftMouseButtonDown(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onLeftMouseButtonDown(), std::move(handle)};
    }

    static MessageHandler onLeftMouseButtonUp(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onLeftMouseButtonUp(), std::move(handle)};
    }

    static MessageHandler onMiddleMouseButtonDown(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onMiddleMouseButtonDown(), std::move(handle)};
    }

    static MessageHandler onMiddleMouseButtonUp(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onMiddleMouseButtonUp(), std::move(handle)};
    }

    static MessageHandler onRightMouseButtonDown(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onRightMouseButtonDown(), std::move(handle)};
    }

    static MessageHandler onRightMouseButtonUp(std::function<void(Window *, const WindowMessage &)> handle) {
        return {WindowMessage::onRightMouseButtonUp(), std::move(handle)};
    }
};

#endif
