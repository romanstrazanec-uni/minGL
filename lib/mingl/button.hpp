#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include <mingl/guiobject.hpp>

class Window;

class Button : public GUIObject {
    Window *window;
    const char *title;
    long id;
    UINT style{WS_VISIBLE | WS_CHILD};
#ifdef USE_WNDCLASSEX
    DWORD extendedStyle;
#endif

    void (*onClick)(){nullptr};

public:
    Button() = default;

    Button(const Button &) = default;

    Button(Window *window, long id, const char *title, int x, int y, int width, int height);

    Button(Window *window, long id, const char *title, int x, int y, int width, int height, void (*onClick)());

    void create() const;

    void addOnClickListener(void (*)());

    void performClick();

    long getId() const;

    const char *getTitle() const;
};

#endif
