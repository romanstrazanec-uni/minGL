#ifndef MINGL_EDITTEXT_INCLUDED
#define MINGL_EDITTEXT_INCLUDED

#include <mingl/gui/guiobject.hpp>

class EditText : public GUIObject {
public:
    EditText(int x, int y, int width, int height);

    EditText(const char *text, int x, int y, int width, int height);

    EditText(Window *parent, int x, int y, int width, int height);

    EditText(Window *parent, const char *text, int x, int y, int width, int height);
};

#endif
