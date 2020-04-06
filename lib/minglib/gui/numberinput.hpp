#ifndef MINGL_NUMBER_INPUT_INCLUDED
#define MINGL_NUMBER_INPUT_INCLUDED

#include "textinput.hpp"

class NumberInput : public TextInput {
public:
    NumberInput(long id, UINT16 x, UINT16 y);
    NumberInput(long id, UINT64 number, UINT16 x, UINT16 y);
    NumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(Window *parent, long id, UINT16 x, UINT16 y);
    NumberInput(Window *parent, long id, UINT64 number, UINT16 x, UINT16 y);
    NumberInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput(Window *parent, long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    UINT64 getNumber() const;
    void setNumber(UINT64);
};

#endif
