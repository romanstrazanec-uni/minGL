#ifndef MINGL_WINDOW_MESSAGE_INCLUDED
#define MINGL_WINDOW_MESSAGE_INCLUDED

#include <windows.h>

/**
 * Stores Windows message code with its WPARAM and LPARAM.
 *
 * Can be created only with the code.
 */
class WindowMessage {
    UINT code;
    WPARAM wParam{0};
    LPARAM lParam{0};

public:
    /**
     * Cannot create empty message. Every message should have a code.
     */
    WindowMessage() = delete;
    WindowMessage(const WindowMessage &);

    /**
     * UINT code can be implicitly converted to the WindowMessage.
     */
    WindowMessage(UINT code);
    WindowMessage(UINT code, WPARAM, LPARAM);

    /* Getters */

    UINT getCode() const;
    WPARAM getWparam() const;
    LPARAM getLparam() const;

    /**
     * Gets mouse position if the code relates to mouse action.
     *
     * @returns structure POINT with {x, y} coordinates of mouse action or {0, 0} if it is not mouse action.
     */
    POINT getMousePosition() const;

    /* Comparators */

    friend bool operator==(const WindowMessage &, UINT);
    friend bool operator!=(const WindowMessage &, UINT);
    friend bool operator==(UINT, const WindowMessage &);
    friend bool operator!=(UINT, const WindowMessage &);
    friend bool operator==(const WindowMessage &msg1, const WindowMessage &msg2);
    friend bool operator!=(const WindowMessage &msg1, const WindowMessage &msg2);

    /* Static Constructors */

    static WindowMessage onCreate();
    static WindowMessage onPaint();
    static WindowMessage onClose();
    static WindowMessage onMouseMove();
    static WindowMessage onLeftMouseButtonDown();
    static WindowMessage onLeftMouseButtonUp();
    static WindowMessage onMiddleMouseButtonDown();
    static WindowMessage onMiddleMouseButtonUp();
    static WindowMessage onRightMouseButtonDown();
    static WindowMessage onRightMouseButtonUp();
};

#endif
