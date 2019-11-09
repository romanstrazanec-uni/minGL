#ifndef MINGL_GUIOBJECT_HPP
#define MINGL_GUIOBJECT_HPP

#include <windows.h>

/**
 * GUI object represents a base class for all components of GUI objects that have a position and size.
 */
class GUIObject {
protected:
    int x, y, width, height;

public:
    GUIObject() = default;

    GUIObject(int x, int y, int width, int height);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;
};

#endif
