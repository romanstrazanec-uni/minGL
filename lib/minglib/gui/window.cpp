#include "window.hpp"

Window::Window() : Window("") {}
Window::Window(const char *title) : Window(title, 100, 100, 400, 400) {}
Window::Window(UINT16 x, UINT16 y, UINT16 width, UINT16 height) : Window("", x, y, width, height) {}
Window::Window(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : BaseWindow(title, x, y, width, height), canvas(this) {
    // todo: create methods that accept handles
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
    addHandler(MessageHandler(std::move(msg), handler)); // todo: trivially copyable
}

void Window::addOnMouseEventHandler(WindowMessage &&wm, MouseHandle onMouseEvent) {
    addHandler(std::move(wm), [&onMouseEvent](Window *w, WindowMessage wm) {
        onMouseEvent(w, wm.getMousePosition());
    });
}

void Window::addOnMouseMoveHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onMouseMove(), std::move(handle));
}
void Window::addOnLeftMouseButtonDownHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onLeftMouseButtonDown(), std::move(handle));
}
void Window::addOnLeftMouseButtonUpHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onLeftMouseButtonUp(), std::move(handle));
}
void Window::addOnMiddleMouseButtonDownHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onMiddleMouseButtonDown(), std::move(handle));
}
void Window::addOnMiddleMouseButtonUpHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onMiddleMouseButtonUp(), std::move(handle));
}
void Window::addOnRightMouseButtonDownHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onRightMouseButtonDown(), std::move(handle));
}
void Window::addOnRightMouseButtonUpHandler(MouseHandle handle) {
    addOnMouseEventHandler(WindowMessage::onRightMouseButtonUp(), std::move(handle));
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

void Window::addLabel(Label *label) { addObject(label); }
Label *Window::addLabel(Label &&label) { return (Label *) addObject(std::move(label)); }
Label *Window::addLabel(long id, const char *text, int x, int y, int width, int height) {
    return new Label(this, id, text, x, y, width, height);
}

/* EditText additions. */

void Window::addEditText(EditText *editText) { addObject(editText); }
EditText *Window::addEditText(EditText &&editText) { return (EditText *) addObject(std::move(editText)); }
EditText *Window::addEditText(long id, int x, int y, int width, int height) {
    return new EditText(this, id, x, y, width, height);
}
EditText *Window::addEditText(long id, const char *text, int x, int y, int width, int height) {
    return new EditText(this, id, text, x, y, width, height);
}

/* Button additions */

void Window::addButton(Button *button) { addObject(button); }
Button *Window::addButton(Button &&button) { return (Button *) addObject(std::move(button)); }
Button *Window::addButton(long id, const char *title, int x, int y, int width, int height) {
    return new Button(this, id, title, x, y, width, height);
}
Button *
Window::addButton(long id, const char *title, int x, int y, int width, int height, OnClickHandle onClick) {
    return new Button(this, id, title, x, y, width, height, std::move(onClick));
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

/* Canvas */

const Canvas &Window::getCanvas() const { return canvas; }

void Window::addOnDrawHandler(std::function<void(Gdiplus::Graphics *)> &&onDraw) {
    canvas.addOnDrawListener(std::move(onDraw));
}

void Window::redraw() {
    if (isCreated()) RedrawWindow(getWindowHandle(), nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}