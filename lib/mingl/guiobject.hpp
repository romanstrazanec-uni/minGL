#ifndef MINGL_GUIOBJECT_HPP
#define MINGL_GUIOBJECT_HPP

#include <windows.h>

class Window;

/**
 * GUI object represents a base class for all components of GUI objects that have a position and size.
 */
class GUIObject {
protected:
    HWND hwnd{nullptr};
    Window *parentWindow;
    const char *className;
    const char *name;
    UINT style;
    int x, y, width, height;
    long id;
#ifdef USE_WNDCLASSEX
    DWORD extendedStyle;
#endif

    GUIObject() = default;

    /** Constructor for GUIObject with no parent window. */
    GUIObject(const char *className, long id, const char *name, int x, int y, int width, int height);

    /** Constructor for child GUIObject. */
    GUIObject(Window *parentWindow, const char *className, long id, const char *name, int x, int y, int width,
              int height);

public:
    bool create();

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    long getId() const;

    bool isCreated() const;
};

#endif
