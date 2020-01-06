#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include "guiobject.hpp"

class Button : public GUIObject {
    void (*onClick)(Window *){};

public:
    Button() = default;
    Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, void (*onClick)(Window *));
    Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height,
           void (*onClick)(Window *));

    void addOnClickListener(void (*)(Window *));

    void removeOnClickListener();

    void performClick();

    const char *getTitle() const;
};

#endif
