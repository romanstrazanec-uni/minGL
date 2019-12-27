#include "window.hpp"

Window::Window() : Window("") {}

Window::Window(const char *title) : Window(title, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) {}

Window::Window(int x, int y, int width, int height) : Window("", x, y, width, height) {}

Window::Window(const char *title, int x, int y, int width, int height) : BaseWindow(title, x, y, width, height) {
    addHandler(Message::onCreate(), [](Window *window, Message msg) { window->createObjects(); });
    addHandler(Message(WM_COMMAND), [](Window *window, Message msg) { window->performClick(msg.getWparam()); });

    initialize();
}

Window::~Window() {
    for (auto objectKVP : objects) delete objectKVP.second;
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

/* Label additions. */

void Window::addLabel(Label *label) {
    label->setParent(this);
    objects[label->getId()] = label;
}

Label *Window::addLabel(Label &&label) {
    label.setParent(this);
    objects[label.getId()] = &label;
    return &label;
}

Label *Window::addLabel(long id, const char *text, int x, int y, int width, int height) {
    return addLabel(Label(this, id, text, x, y, width, height));
}

/* EditText additions. */

void Window::addEditText(EditText *editText) {
    editText->setParent(this);
    objects[editText->getId()] = editText;
}

EditText *Window::addEditText(EditText &&editText) {
    editText.setParent(this);
    objects[editText.getId()] = &editText;
    return &editText;
}

EditText *Window::addEditText(long id, int x, int y, int width, int height) {
    return addEditText(EditText(this, id, x, y, width, height));
}

EditText *Window::addEditText(long id, const char *text, int x, int y, int width, int height) {
    return addEditText(EditText(this, id, text, x, y, width, height));
}

/* Button additions. */

void Window::addButton(Button *button) {
    button->setParent(this);
    objects[button->getId()] = button;
}

Button *Window::addButton(Button &&button) {
    button.setParent(this);
    objects[button.getId()] = &button;
    return &button;
}

Button *Window::addButton(long id, const char *title, int x, int y, int width, int height) {
    Button *button = new Button(this, id, title, x, y, width, height);
    objects[id] = button;
    return button;
}

Button *Window::addButton(long id, const char *title, int x, int y, int width, int height,
                          std::function<void()> onClick) {
    Button *button = new Button(this, id, title, x, y, width, height, onClick);
    objects[id] = button;
    return button;
}

bool Window::remove(GUIObject *object) {
    for (std::map<long, GUIObject *>::const_iterator it = objects.begin(); it != objects.end(); it++)
        // todo: maybe delete?
        if ((*it).second == object) {
            objects.erase(it);
            return true;
        }
    return false;
}

bool Window::remove(Label *label) {
    return remove((GUIObject *) label);
}

bool Window::remove(EditText *editText) {
    return remove((GUIObject *) editText);
}

bool Window::remove(Button *button) {
    return remove((GUIObject *) button);
}

GUIObject *Window::find(long id) {
    // todo: map has find method
    for (auto objectKVP : objects)
        if (objectKVP.second->getId() == id) return objectKVP.second;
    return nullptr;
}

void Window::createObjects() {
    if (!isCreated()) return;
    for (auto objectKVP : objects) objectKVP.second->create();
}

void Window::performClick(long id) {
    if (isCreated()) {
        // todo: maybe use window find method?
        std::map<long, GUIObject *>::const_iterator it = objects.find(id);
        if (it != objects.end()) {
            Button *button = dynamic_cast<Button *>((*it).second);
            if (button != nullptr) button->performClick();
        }
    }
}
