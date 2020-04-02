#ifndef MINGL_EDITTEXT_INCLUDED
#define MINGL_EDITTEXT_INCLUDED

#include "guiobject.hpp"

class EditText : public GUIObject {
public:
    EditText(long id, UINT16 x, UINT16 y);
    EditText(long id, const char *text, UINT16 x, UINT16 y);
    EditText(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    EditText(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    EditText(Window *parent, long id, UINT16 x, UINT16 y);
    EditText(Window *parent, long id, const char *text, UINT16 x, UINT16 y);
    EditText(Window *parent, long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    EditText(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

protected:
    void computeSize() override;
};

#endif
