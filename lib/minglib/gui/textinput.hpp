#ifndef MINGL_TEXT_INPUT_INCLUDED
#define MINGL_TEXT_INPUT_INCLUDED

#include "guiobject.hpp"

class TextInput : public GUIObject {
public:
    TextInput(long id, UINT16 x, UINT16 y);
    TextInput(long id, const char *text, UINT16 x, UINT16 y);
    TextInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    TextInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    TextInput(Window *parent, long id, UINT16 x, UINT16 y);
    TextInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y);
    TextInput(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    TextInput(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    void addBorder();
    void alignLeft();
    void alignCenter();
    void alignRight();
    void enableVerticalScroll();
    void enableHorizontalScroll();
    void enableVerticalAutoScroll();
    void enableHorizontalAutoScroll();
    void enableMultiLine();
    void readOnly();

protected:
    void computeSize() override;
};

#endif
