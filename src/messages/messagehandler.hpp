#ifndef MINGL_MESSAGE_HANDLER_INCLUDED
#define MINGL_MESSAGE_HANDLER_INCLUDED

#include "windowmessage.hpp"

#include <functional>

class Window;

typedef std::function<void(Window *, const WindowMessage &)> Handle;

/**
 * Handles certain message with handle.
 */
class MessageHandler {
    /**
     * Message handler handles
     */
    WindowMessage message;

    /**
     * Function
     */
    Handle handle;

public:
    /**
     * Cannot be without message and a function.
     */
    MessageHandler() = delete;

    /**
     * Cannot be copied.
     */
    MessageHandler(const MessageHandler &) = delete;

    MessageHandler(WindowMessage &&, const Handle &);

    /**
     * Handles WindowMessage if it equals to the specified.
     */
    void handleMessage(Window *, const WindowMessage &);

    /**
     * Gets the message, which also stores WPARAM and LPARAM.
     *
     * @return unmodifiable reference.
     */
    const WindowMessage &getMessage() const;
};

#endif
