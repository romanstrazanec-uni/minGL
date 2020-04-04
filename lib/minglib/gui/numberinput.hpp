#ifndef MINGL_NUMBERINPUT_INCLUDED
#define MINGL_NUMBERINPUT_INCLUDED

#include "textinput.hpp"

class NumberInput : public TextInput {
public:
    NumberInput(long id, UINT16 x, UINT16 y);
    NumberInput(long id, const char *text, UINT16 x, UINT16 y);
    NumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(Window *parent, long id, UINT16 x, UINT16 y);
    NumberInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y);
    NumberInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
};

#endif
