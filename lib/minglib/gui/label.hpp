#ifndef MINGL_LABEL_INCLUDED
#define MINGL_LABEL_INCLUDED

#include "guiobject.hpp"

class Label : public GUIObject {
public:
    Label(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Label(Window *parent, long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
};

#endif
