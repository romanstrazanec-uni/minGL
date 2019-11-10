#include "window.hpp"
#include "button.hpp"

Window::Window() {
    addHandler(Message::onCreate(), [](Window *window, Message msg) { window->createButtons(); });
    addHandler(Message(WM_COMMAND), [](Window *window, Message msg) { window->performClick(msg.getWparam()); });
}

LRESULT Window::handleMessage(Message msg) {
    if (messageHandlers.count(msg.getMsg()) == 0)
        return DefWindowProc(getWindowHandle(), msg.getMsg(), msg.getWparam(), msg.getLparam());
    messageHandlers[msg.getMsg()].handleMessage(this, msg);
    return 0;
}

void Window::addHandler(MessageHandler msgHandler) {
    messageHandlers[msgHandler.getMessage().getMsg()] = msgHandler;
}

void Window::addHandler(Message msg, void (*handler)(Window *, Message)) {
    addHandler(MessageHandler(msg, handler));
}

void Window::addButton(Button *btn) {
    buttons[btn->getId()] = *btn;
}

Button *Window::addButton(const char *title, long id, int x, int y, int width, int height) {
    buttons[id] = Button(this, id, title, x, y, width, height);
    return &buttons[id];
}

Button *Window::addButton(const char *title, long id, int x, int y, int width, int height, void (*onClick)()) {
    buttons[id] = Button(this, id, title, x, y, width, height, onClick);
    return &buttons[id];
}

void Window::createButtons() {
    for (auto &i : buttons) i.second.create();
}

void Window::performClick(long id) {
    buttons[id].performClick();
}
