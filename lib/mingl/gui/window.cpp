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
    for (auto button : buttons) delete button.second;
    for (auto label : labels) delete label;
    for (auto editText : editTexts) delete editText;
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
    labels.push_front(label);
}

Label *Window::addLabel(Label &&label) {
    label.setParent(this);
    labels.push_front(&label);
    return *labels.begin();
}

Label *Window::addLabel(const char *text, int x, int y, int width, int height) {
    return addLabel(Label(this, text, x, y, width, height));
}

/* EditText additions. */

void Window::addEditText(EditText *editText) {
    editText->setParent(this);
    editTexts.push_front(editText);
}

EditText *Window::addEditText(EditText &&editText) {
    editText.setParent(this);
    editTexts.push_front(&editText);
    return *editTexts.begin();
}

EditText *Window::addEditText(int x, int y, int width, int height) {
    return addEditText(EditText(this, x, y, width, height));
}

EditText *Window::addEditText(const char *text, int x, int y, int width, int height) {
    return addEditText(EditText(this, text, x, y, width, height));
}

/* Button additions. */

void Window::addButton(Button *button) {
    if (button->getId() == 0L) return;
    button->setParent(this);
    buttons[button->getId()] = button;
}

Button *Window::addButton(Button &&button) {
    if (button.getId() == 0L) return nullptr;
    button.setParent(this);
    buttons[button.getId()] = &button;
    return buttons[button.getId()];
}

Button *Window::addButton(const char *title, long id, int x, int y, int width, int height) {
    if (id == 0L) return nullptr;
    Button *button = new Button(this, id, title, x, y, width, height);
    buttons[id] = button;
    return button;
}

Button *
Window::addButton(const char *title, long id, int x, int y, int width, int height, std::function<void()> onClick) {
    if (id == 0L) return nullptr;
    Button *button = new Button(this, id, title, x, y, width, height, onClick);
    buttons[id] = button;
    return button;
}

bool Window::remove(GUIObject *object) {
    for (std::map<long, Button *>::const_iterator it = buttons.begin(); it != buttons.end(); it++)
        if ((*it).second == object) {
            buttons.erase(it);
            return true;
        }
    for (std::list<Label *>::const_iterator it = labels.begin(); it != labels.end(); it++)
        if (*it == object) {
            labels.erase(it);
            return true;
        }
    for (std::list<EditText *>::const_iterator it = editTexts.begin(); it != editTexts.end(); it++)
        if (*it == object) {
            editTexts.erase(it);
            return true;
        }
    return false;
}

bool Window::remove(Label *label) {
    for (std::list<Label *>::const_iterator it = labels.begin(); it != labels.end(); it++)
        if (*it == label) {
            labels.erase(it);
            return true;
        }
    return false;
}

bool Window::remove(EditText *editText) {
    for (std::list<EditText *>::const_iterator it = editTexts.begin(); it != editTexts.end(); it++)
        if (*it == editText) {
            editTexts.erase(it);
            return true;
        }
    return false;
}

bool Window::remove(Button *button) {
    for (std::map<long, Button *>::const_iterator it = buttons.begin(); it != buttons.end(); it++)
        if ((*it).second == button) {
            buttons.erase(it);
            return true;
        }
    return false;
}

void Window::createObjects() {
    if (!isCreated()) return;
    for (auto buttonKVP : buttons) buttonKVP.second->create();
    for (auto label : labels) label->create();
    for (auto editText : editTexts) editText->create();
}

void Window::performClick(long id) {
    if (isCreated()) {
        std::map<long, Button *>::const_iterator it = buttons.find(id);
        if (it != buttons.end()) (*it).second->performClick();
    }
}
