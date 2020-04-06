#include "numberinput.hpp"

NumberInput::NumberInput(long id, UINT16 x, UINT16 y)
        : NumberInput(nullptr, id, x, y) {}
NumberInput::NumberInput(long id, UINT64 number, UINT16 x, UINT16 y)
        : NumberInput(nullptr, id, number, x, y) {}
NumberInput::NumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : NumberInput(nullptr, id, x, y, width, height) {}
NumberInput::NumberInput(long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : NumberInput(nullptr, id, number, x, y, width, height) {}
NumberInput::NumberInput(Window *parent, long id, UINT16 x, UINT16 y)
        : NumberInput(parent, id, x, y, 0, 0) {}
NumberInput::NumberInput(Window *parent, long id, UINT64 number, UINT16 x, UINT16 y)
        : NumberInput(parent, id, number, x, y, 0, 0) {}
NumberInput::NumberInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(parent, id, "", x, y, width, height) {
    addStyle(ES_NUMBER);
}
NumberInput::NumberInput(Window *parent, long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(parent, id, std::to_string(number).c_str(), x, y, width, height) {
    addStyle(ES_NUMBER);
}

UINT64 NumberInput::getNumber() const {
    std::string text = getText();
    return text.empty() ? 0 : std::stoul(text);
}
void NumberInput::setNumber(UINT64 number) {
    setText(std::to_string(number).c_str());
}
