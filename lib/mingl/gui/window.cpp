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
    for (auto it = objects.begin(); it != objects.end(); it = objects.begin()) {
        GUIObject *o = it->second;
        objects.erase(it);
        delete o;
    }
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

void Window::addObject(GUIObject *object) {
    object->setParent(this);
    objects.insert(std::make_pair(object->getId(), object));
}

template<class Object>
Object *Window::addObject(Object &&object) {
    Object *newObject = new Object(object);
    addObject(newObject);
    return newObject;
}

/* Label additions. */

void Window::addLabel(Label *label) {
    addObject(label);
}

Label *Window::addLabel(Label &&label) {
    return (Label *) addObject(std::move(label));
}

Label *Window::addLabel(long id, const char *text, int x, int y, int width, int height) {
    return new Label(this, id, text, x, y, width, height);
}

/* EditText additions. */

void Window::addEditText(EditText *editText) {
    addObject(editText);
}

EditText *Window::addEditText(EditText &&editText) {
    return (EditText *) addObject(std::move(editText));
}

EditText *Window::addEditText(long id, int x, int y, int width, int height) {
    return new EditText(this, id, x, y, width, height);
}

EditText *Window::addEditText(long id, const char *text, int x, int y, int width, int height) {
    return new EditText(this, id, text, x, y, width, height);
}

/* Button additions. */

void Window::addButton(Button *button) {
    addObject(button);
}

Button *Window::addButton(Button &&button) {
    return (Button *) addObject(std::move(button));
}

Button *Window::addButton(long id, const char *title, int x, int y, int width, int height) {
    return new Button(this, id, title, x, y, width, height);
}

Button *
Window::addButton(long id, const char *title, int x, int y, int width, int height, std::function<void()> onClick) {
    return new Button(this, id, title, x, y, width, height, onClick);
}

GUIObject *Window::find(long id) {
    std::map<long, GUIObject *>::const_iterator it = objects.find(id);
    return it != objects.end() ? it->second : nullptr;
}

void Window::createObjects() {
    if (!isCreated()) return;
    for (auto objectKVP : objects) objectKVP.second->create();
}

void Window::performClick(long id) {
    if (isCreated()) {
        GUIObject *obj = find(id);
        if (obj != nullptr) {
            Button *button = dynamic_cast<Button *>(obj);
            if (button != nullptr) button->performClick();
        }
    }
}
