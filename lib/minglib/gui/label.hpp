#ifndef MINGL_LABEL_INCLUDED
#define MINGL_LABEL_INCLUDED

#include "guiobject.hpp"

class Label : public GUIObject {
public:
    Label(long id, const char *text, int x, int y, int width, int height);
    Label(Window *parent, long id, const char *text, int x, int y, int width, int height);
};

#endif
