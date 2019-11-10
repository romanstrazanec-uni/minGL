#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include <mingl/guiobject.hpp>

class Button : public GUIObject {
    void (*onClick)();

public:
    Button() = default;

    Button(const Button &) = default;

    Button(Window *window, long id, const char *title, int x, int y, int width, int height);

    Button(Window *window, long id, const char *title, int x, int y, int width, int height, void (*onClick)());

    void addOnClickListener(void (*)());

    void performClick();

    const char *getTitle() const;
};

#endif
