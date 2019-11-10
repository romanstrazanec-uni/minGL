#ifndef MINGL_LABEL_INCLUDED
#define MINGL_LABEL_INCLUDED

#include <mingl/guiobject.hpp>

class Label : public GUIObject {
public:
    Label(Window *parent, const char *text, int x, int y, int width, int height);
};

#endif
