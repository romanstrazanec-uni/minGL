#ifndef MINGL_GUIOBJECT_INCLUDED
#define MINGL_GUIOBJECT_INCLUDED

#include <windows.h>
#include <string>

class Window;

/**
 * GUI object represents a base class for all components of GUI objects that have a position and size.
 */
class GUIObject {
    /**
     * Window class name to be registered inside the operating system.
     */
    const char *className{};

    /**
     * Content of the object.
     */
    const char *name{};

    /**
     * Style of the object - usually with the WS prefix in Windows API.
     * To add style use the binary or | operator.
     * To remove style use the binary xor ^ operator.
     */
    UINT style{WS_VISIBLE};

    /**
     * Extended style of the object - usually with the WS_EX prefix in Windows API.
     */
    DWORD extendedStyle{0};

    /**
     * Coordinates and size of the object.
     */
    UINT16 x{}, y{}, width{0}, height{0};

    /**
     * ID of the object.
     * Used for referencing the object.
     */
    long id{0x00FFFFFFL};

    HINSTANCE hInstance{nullptr};
    LPVOID additionalData{nullptr};
    HWND hWnd{nullptr};

protected:
    HMENU hMenu{nullptr};
    Window *parent{nullptr};

    /**
     * Allow construction from temporary object.
     */
    GUIObject(GUIObject &&) = default;

    /**
     * Constructor for GUIObject with no parent window.
     */
    GUIObject(
            const char *className,
            const char *name,
            UINT16 x,
            UINT16 y,
            UINT16 width,
            UINT16 height,
            HINSTANCE,
            LPVOID
    );

    /**
     * Constructor for child GUIObject.
     */
    GUIObject(
            Window *parent,
            const char *className,
            long id,
            const char *name,
            UINT16 x,
            UINT16 y,
            UINT16 width,
            UINT16 height
    );

    virtual const char *getClassName() const final;
    virtual HINSTANCE getInstance() const final;

    virtual void setWidth(UINT16) final;
    virtual void setHeight(UINT16) final;

public:
    /**
     * Cannot be created without parameters.
     */
    GUIObject() = delete;

    /**
     * Cannot be copied.
     */
    GUIObject(const GUIObject &) = delete;
    virtual ~GUIObject();

    /**
     * Uses windows CreateWindow function to create a window. If creation successful, the result
     * of the CreateWindow function is a window handle and is stored as a property of the class.
     *
     * @returns true if creation was successful.
     */
    virtual bool create() final;

    /**
     * Adds style to the object.
     */
    virtual void addStyle(UINT) final;

    /**
     * Removes style from the object.
     */
    virtual void removeStyle(UINT) final;

    virtual const char *getName() const final;

    /**
     * Override this method to compute size before creating object.
     */
    virtual void computeSize() = 0;

    virtual UINT16 getX() const final;
    virtual UINT16 getY() const final;

    virtual UINT16 getWidth() const final;
    virtual UINT16 getHeight() const final;

    virtual long getId() const final;

    virtual HWND getWindowHandle() const final;

    /**
     * @returns true after create() method returned true (Window handle is not nullptr).
     */
    virtual bool isCreated() const final;

    /**
     * Sets the parent of this object.
     *
     * @param onlySet: default = false => removes from the parent first,
     *          sets the given Window parameter as parent and adds to the parent.
     */
    virtual void setParent(Window *, bool onlySet = false) final;

    /**
     * If parent is not nullptr, adds this object to the Window parent.
     */
    virtual void addToParent() final;

    /**
     * If parent is not nullptr, removes this object from the Window parent.
     */
    virtual void removeFromParent() final;

    virtual void setName(const char *) final;

    /**
     * Get text from created object by GetWindowText(HWND, LPSTR, UINT) with specified length.
     * If length is 0, whole text is returned.
     */
    virtual std::string getText(UINT16 length = 0) final;

    virtual void setText(const char *) final;

    /* Comparision operators */

    /**
     * Objects are equal if they have the same id.
     */
    virtual bool operator==(const GUIObject &) const final;
    virtual bool operator!=(const GUIObject &) const final;
    virtual bool operator<(const GUIObject &) const final;
    virtual bool operator>(const GUIObject &) const final;
    virtual bool operator<=(const GUIObject &) const final;
    virtual bool operator>=(const GUIObject &) const final;
};

#endif
