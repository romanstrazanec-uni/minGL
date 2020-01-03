#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include <mingl/gui/guiobject.hpp>

class Button : public GUIObject {
    void (*onClick)(Window *);

public:
    Button() = default;

    Button(long id, const char *title, int x, int y, int width, int height);

    Button(long id, const char *title, int x, int y, int width, int height, void (*onClick)(Window *));

    Button(Window *window, long id, const char *title, int x, int y, int width, int height);

    Button(Window *window, long id, const char *title, int x, int y, int width, int height,
           void (*onClick)(Window *));

    void addOnClickListener(void (*)(Window *));

    void removeOnClickListener();

    void performClick();

    const char *getTitle() const;
};

#endif
