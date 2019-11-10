#ifndef MINGL_GUIOBJECT_HPP
#define MINGL_GUIOBJECT_HPP

#include <windows.h>

class Window;

/**
 * GUI object represents a base class for all components of GUI objects that have a position and size.
 */
class GUIObject {
    const char *className;
    const char *name;
    UINT style{WS_VISIBLE};
#ifdef USE_WNDCLASSEX
    DWORD extendedStyle;
#endif
    int x, y, width, height;
    long id{0};
    HINSTANCE hinstance{nullptr};
    LPVOID additionalData{nullptr};

    Window *parent{nullptr};
    HWND hwnd{nullptr};

protected:

    GUIObject() = default;

    /** Constructor for GUIObject with no parent window. */
    GUIObject(const char *className, const char *name, int x, int y, int width, int height, HINSTANCE, LPVOID);

    /** Constructor for child GUIObject. */
    GUIObject(Window *parent, const char *className, long id, const char *name, int x, int y, int width, int height);

    virtual const char *getClassName() const final;

    virtual HINSTANCE getHinstance() const final;

    virtual LPVOID getAdditionalData() const final;

    virtual void setWindowHandle(HWND) final;

public:
    virtual bool create() final;

    virtual void addStyle(UINT style) final;

    virtual const char *getName() const final;

    virtual int getX() const final;

    virtual int getY() const final;

    virtual int getWidth() const final;

    virtual int getHeight() const final;

    virtual long getId() const final;

    virtual HWND getWindowHandle() const final;

    virtual bool isCreated() const final;

    virtual void setName(const char *) final;
};

#endif
