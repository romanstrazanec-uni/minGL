#include "messagehandler.hpp"

MessageHandler::MessageHandler(WindowMessage &&msg, const Handle &handle)
        : message(msg), handle(handle) {}

void MessageHandler::handleMessage(const WindowMessage &msg) {
    // Handle only if message codes are equal.
    if (message == msg) {
        // Store the params.
        message = msg;
        handle(message);
    }
}

const WindowMessage &MessageHandler::getMessage() const { return message; }
