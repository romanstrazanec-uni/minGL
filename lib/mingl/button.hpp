#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include <windows.h>

class Window;

class Button {
    Window *window;
    const char *title;
    long id;
    int x, y, width, height;
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

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;
};

#endif
