#include "window.hpp"

Window::Window(const char *title) : Window(title, 100, 50) {}
Window::Window(UINT16 x, UINT16 y) : Window("", x, y) {}
Window::Window(UINT16 x, UINT16 y, UINT16 width, UINT16 height) : Window("", x, y, width, height) {}
Window::Window(const char *title, UINT16 x, UINT16 y) : Window(title, x, y, 0, 0) {}
Window::Window(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : BaseWindow(title, x, y, width, height), canvas(this) {
    // todo: create methods that accept handles
    addHandler(MessageHandler::onCreate([](Window *window, WindowMessage msg) { window->createObjects(); }));
    addHandler(WindowMessage(WM_COMMAND), [](Window *window, WindowMessage msg) {
        window->performClick(msg.getWparam());
    });

    initialize();
}

void Window::setWindowAttributes() {
    setIcon(IDI_APPLICATION);
    setSmallIcon(IDI_APPLICATION);
    setCursor(IDI_APPLICATION);
    setBackground((HBRUSH) COLOR_WINDOW);
    setMenuName(nullptr);
    setStyle(0);
    setWindowExtraBytes(0);
    setClassExtraBytes(0);
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
    addHandler(std::move(wm), [&onMouseEvent](Window *, WindowMessage wm) {
        POINT mousePosition = wm.getMousePosition();
        onMouseEvent(Gdiplus::Point(mousePosition.x, mousePosition.y));
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

/* Label additions. */

void Window::addLabel(Label *label) { addObject(label); }
Label *Window::addLabel(Label &&label) { return (Label *) addObject(std::move(label)); }
Label *Window::addLabel(long id, const char *text, UINT16 x, UINT16 y) {
    return new Label(this, id, text, x, y);
}
Label *Window::addLabel(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height) {
    return new Label(this, id, text, x, y, width, height);
}

/* TextInput additions. */

void Window::addTextInput(TextInput *textInput) { addObject(textInput); }
TextInput *Window::addTextInput(TextInput &&textInput) { return (TextInput *) addObject(std::move(textInput)); }
TextInput *Window::addTextInput(long id, UINT16 x, UINT16 y) {
    return new TextInput(this, id, x, y);
}
TextInput *Window::addTextInput(long id, const char *text, UINT16 x, UINT16 y) {
    return new TextInput(this, id, text, x, y);
}
TextInput *Window::addTextInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height) {
    return new TextInput(this, id, x, y, width, height);
}
TextInput *Window::addTextInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height) {
    return new TextInput(this, id, text, x, y, width, height);
}

/* NumberInput additions. */

void Window::addNumberInput(NumberInput *numberInput) { addObject(numberInput); }
NumberInput *Window::addNumberInput(NumberInput &&numberInput) {
    return (NumberInput *) addObject(std::move(numberInput));
}
NumberInput *Window::addNumberInput(long id, UINT16 x, UINT16 y) {
    return new NumberInput(this, id, x, y);
}
NumberInput *Window::addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y) {
    return new NumberInput(this, id, number, x, y);
}
NumberInput *Window::addNumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height) {
    return new NumberInput(this, id, x, y, width, height);
}
NumberInput *Window::addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height) {
    return new NumberInput(this, id, number, x, y, width, height);
}

/* Button additions */

void Window::addButton(Button *button) { addObject(button); }
Button *Window::addButton(Button &&button) { return (Button *) addObject(std::move(button)); }
Button *Window::addButton(long id, const char *title, UINT16 x, UINT16 y, OnClickHandle &&onClick) {
    return new Button(this, id, title, x, y, std::move(onClick));
}
Button *
Window::addButton(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height,
                  OnClickHandle &&onClick) {
    return new Button(this, id, title, x, y, width, height, std::move(onClick));
}

void Window::createObjects() {
    if (!isCreated()) return;
    for (auto objectKVP : objects) objectKVP.second->create();
}

void Window::computeSize() {
    UINT16 computedWidth = 0, computedHeight = 0, newWidth, newHeight;
    for (auto objectKVP : objects) {
        objectKVP.second->computeSize();

        newWidth = objectKVP.second->getX() + objectKVP.second->getWidth();
        computedWidth = newWidth > computedWidth ? newWidth : computedWidth;

        newHeight = objectKVP.second->getY() + objectKVP.second->getHeight();
        computedHeight = newHeight > computedHeight ? newHeight : computedHeight;
    }

    if (computedWidth + 10 > getWidth()) setWidth(computedWidth + 10);
    if (computedHeight + 10 > getHeight()) setHeight(computedHeight + 10);
    setHeight(getHeight() + 25);
}

void Window::performClick(long id) {
    if (isCreated()) {
        auto button = find<Button>(id);
        if (button != nullptr) button->performClick();
    }
}

bool Window::showMessageDialog(const char *title, const char *message) const {
    return isCreated() && MessageBox(getWindowHandle(), message, title, MB_OKCANCEL) == IDOK;
}

/* Canvas */

Canvas &Window::getCanvas() { return canvas; }

void Window::addOnDrawHandler(OnDrawHandle &&onDraw) {
    canvas.addOnDrawListener(std::move(onDraw));
}

void Window::redraw() {
    if (isCreated())
        RedrawWindow(getWindowHandle(), nullptr, nullptr,
                     RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
