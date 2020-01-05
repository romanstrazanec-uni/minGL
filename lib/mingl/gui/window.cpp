#include "window.hpp"

Window::Window() : Window("") {}

Window::Window(const char *title) : Window(title, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) {}

Window::Window(int x, int y, int width, int height) : Window("", x, y, width, height) {}

Window::Window(const char *title, int x, int y, int width, int height) : BaseWindow(title, x, y, width, height) {
    addHandler(MessageHandler::onCreate([](Window *window, WindowMessage msg) { window->createObjects(); }));
    addHandler(WindowMessage(WM_COMMAND),
               [](Window *window, WindowMessage msg) { window->performClick(msg.getWparam()); });

    initialize();
}

Window::~Window() {
    for (auto it = objects.begin(); it != objects.end(); it = objects.begin()) {
        GUIObject *o = it->second;
        o->setParent(nullptr, true);
        objects.erase(it);
        delete o;
    }
}

/* Message handling */

LRESULT Window::handleMessage(WindowMessage &&msg) {
    auto mh = messageHandlers.find(msg.getMsg());
    if (mh == messageHandlers.end())
        return DefWindowProc(getWindowHandle(), msg.getMsg(), msg.getWparam(), msg.getLparam());
    messageHandlers[msg.getMsg()].handleMessage(this, msg);
    return 0;
}

void Window::addHandler(MessageHandler &&msgHandler) {
    messageHandlers[msgHandler.getMessage().getMsg()] = msgHandler;
}

void Window::addHandler(WindowMessage &&msg, Handle &&handler) {
    addHandler(MessageHandler(std::move(msg), handler));
}

void Window::addOnMouseMoveHandler(std::function<void(Window *, POINT)> &&onMouseMove) {
    addHandler(MessageHandler::onMouseMove([&onMouseMove](Window *w, WindowMessage wm) {
        onMouseMove(w, wm.getMousePosition());
    }));
}

/* Object manipulation */

void Window::addObject(GUIObject *object, bool onlyAdd) {
    if (!onlyAdd) object->setParent(this);
    objects.insert(std::make_pair(object->getId(), object));
}

template<class Object>
Object *Window::addObject(Object &&object) {
    auto newObject = new Object(object);
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
Window::addButton(long id, const char *title, int x, int y, int width, int height, void (*onClick)(Window *)) {
    return new Button(this, id, title, x, y, width, height, onClick);
}

void Window::createObjects() {
    if (!isCreated()) return;
    for (auto objectKVP : objects) objectKVP.second->create();
}

void Window::performClick(long id) {
    if (isCreated()) {
        auto button = find<Button>(id);
        if (button != nullptr) button->performClick();
    }
}
