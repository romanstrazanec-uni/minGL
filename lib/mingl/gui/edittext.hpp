#ifndef MINGL_EDITTEXT_INCLUDED
#define MINGL_EDITTEXT_INCLUDED

#include <mingl/gui/guiobject.hpp>

class EditText : public GUIObject {
public:
    EditText(long id, int x, int y, int width, int height);

    EditText(long id, const char *text, int x, int y, int width, int height);

    EditText(Window *parent, long id, int x, int y, int width, int height);

    EditText(Window *parent, long id, const char *text, int x, int y, int width, int height);
};

#endif
