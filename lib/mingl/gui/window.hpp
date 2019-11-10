#ifndef MINGL_WINDOW_INCLUDED
#define MINGL_WINDOW_INCLUDED

#include <map>

#include <mingl/gui/basewindow.hpp>
#include <mingl/gui/button.hpp>
#include <mingl/messagehandler.hpp>

/**
 * Derived main Window to create and show window.
 */
class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers;
    std::map<long, Button> buttons;
public:
    Window();

    LRESULT handleMessage(Message) override;

    /** Adds a message handler to respond to window messages. */
    void addHandler(MessageHandler);

    /** Adds a message handler to respond to specified message with handle function. */
    void addHandler(Message, void (*handler)(Window *, Message));

    /** Assigns created button to the window. */
    void addButton(Button *btn);

    /**
     * Adds a button with specified title at certain position relative to the window.
     * Assign id to the button to respond with later assigned onClick method.
     *
     * @returns pointer to the newly created button.
     */
    Button *addButton(const char *title, long id, int x, int y, int width, int height);

    /**
     * Adds a button with specified title at certain position relative to the window.
     * Assign id to the button to respond with assigned onClick method.
     *
     * @returns pointer to the newly created button.
     */
    Button *addButton(const char *title, long id, int x, int y, int width, int height, void (*onClick)());

    /** Creates windows for all assigned buttons when window is created. */
    void createButtons();

    /** Performs click on a button found by id. If not found, nothing happens. */
    void performClick(long id);
};

#endif
