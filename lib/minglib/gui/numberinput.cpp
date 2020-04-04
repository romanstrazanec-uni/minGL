#include "numberinput.hpp"

NumberInput::NumberInput(long id, UINT16 x, UINT16 y)
        : NumberInput(nullptr, id, x, y) {}
NumberInput::NumberInput(long id, const char *text, UINT16 x, UINT16 y)
        : NumberInput(nullptr, id, text, x, y) {}
NumberInput::NumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : NumberInput(id, "", x, y, width, height) {}
NumberInput::NumberInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : NumberInput(nullptr, id, text, x, y, width, height) {}
NumberInput::NumberInput(Window *parent, long id, UINT16 x, UINT16 y)
        : NumberInput(parent, id, "", x, y) {}
NumberInput::NumberInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y)
        : NumberInput(parent, id, text, x, y, 0, 0) {}
NumberInput::NumberInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : NumberInput(parent, id, "", x, y, width, height) {}
NumberInput::NumberInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height)
        : TextInput(parent, id, text, x, y, width, height) {
    addStyle(ES_NUMBER);
}
