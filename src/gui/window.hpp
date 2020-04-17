#ifndef MINGL_WINDOW_INCLUDED
#define MINGL_WINDOW_INCLUDED

#include "basewindow.hpp"
#include "button.hpp"
#include "numberinput.hpp"
#include "label.hpp"

#include "../messages/messagehandler.hpp"
#include "../graphics/canvas.hpp"

#include <map>

typedef std::function<void(const Gdiplus::Point &)> MouseHandle;

/**
 * Derived main Window to create and show window.
 */
class Window final : public BaseWindow<Window> {
    /**
     * Stores pointers to heap allocated message handlers (using method addHandler).
     * Finds handler by message code.
     */
    std::map<UINT, MessageHandler *> messageHandlers{};

    /**
     * Stores pointers object to heap allocated GUI objects (using method addObject).
     * Finds object by id.
     */
    std::map<long, GUIObject *> objects{};

    /**
     * Window's canvas.
     */
    Canvas canvas;

    /**
     * Add handler for mouse action.
     */
    void addOnMouseEventHandler(WindowMessage &&, MouseHandle &&);

    /**
     * Sets attributes to WNDCLASSEX.
     */
    void setWindowAttributes() override;

    LRESULT handleMessage(WindowMessage &&) override;

    /**
     * Compute size before creation according to the child objects.
     */
    void computeSize() override;

public:
    /**
     * Construct Window explicitly with default empty title.
     *
     * Default position is at {100, 50} and size will be computed automatically with its child objects.
     */
    explicit Window(const char *title = "");

    /**
     * Construct Window on specified coordinates.
     *
     * Size will be computed automatically with its child objects.
     */
    Window(UINT16 x, UINT16 y);

    /**
     * Construct Window on specified coordinates with specified size.
     */
    Window(UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /**
     * Construct Window with the title on specified coordinates.
     *
     * Size will be computed automatically with its child objects.
     */
    Window(const char *title, UINT16 x, UINT16 y);

    /**
     * Construct Window with the title on specified coordinates with specified size.
     */
    Window(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    ~Window() override;

    /* Message handling */

    /**
     * Adds a message handler to respond to specified message with handle function.
     */
    void addHandler(WindowMessage &&, Handle &&);

    void addOnMouseMoveHandler(MouseHandle &&);
    void addOnLeftMouseHandler(MouseHandle &&);
    void addOnLeftMouseUpHandler(MouseHandle &&);
    void addOnMiddleMouseHandler(MouseHandle &&);
    void addOnMiddleMouseUpHandler(MouseHandle &&);
    void addOnRightMouseHandler(MouseHandle &&);
    void addOnRightMouseUpHandler(MouseHandle &&);

    /* Object manipulation */

    /**
     * Allows addition of GUIObjects passed as an temporary value.
     * Template class Object should be subclass of GUIObject.
     *
     * @tparam subclass of GUIObject.
     * @returns a pointer allocated for the passed object stored in the window.
     */
    template<class Object, typename = std::enable_if<std::is_base_of<GUIObject, Object>::value>>
    Object *addObject(Object &&object) {
        auto newObject = new Object(std::move(object));
        addObject(newObject);
        return newObject;
    }

    /**
     * Adds an created object to window.
     *
     * @param onlyAdd: default = false => firstly sets the parent of the object to this window.
     */
    void addObject(GUIObject *, bool onlyAdd = false);

    /* Label additions. */

    void addLabel(Label *);
    Label *addLabel(long id, const char *text, UINT16 x, UINT16 y);
    Label *addLabel(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* TextInput additions. */

    void addTextInput(TextInput *);
    TextInput *addTextInput(long id, UINT16 x, UINT16 y);
    TextInput *addTextInput(long id, const char *text, UINT16 x, UINT16 y);
    TextInput *addTextInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    TextInput *addTextInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* NumberInput additions. */

    void addNumberInput(NumberInput *);
    NumberInput *addNumberInput(long id, UINT16 x, UINT16 y);
    NumberInput *addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y);
    NumberInput *addNumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput *addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* Button additions. */

    void addButton(Button *);
    Button *addButton(long id, const char *title, UINT16 x, UINT16 y, OnClickHandle && = nullptr);
    Button *
    addButton(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, OnClickHandle && = nullptr);

    /**
     * Removes object from window.
     *
     * @returns true if found and removed.
     */
    template<class Object, typename = std::enable_if<std::is_base_of<GUIObject, Object>::value>>
    bool remove(Object *object) {
        for (std::map<long, GUIObject *>::const_iterator it = objects.begin(); it != objects.end(); ++it)
            if (it->second == object) {
                objects.erase(it);
                object->setParent(nullptr, true);
                return true;
            }
        return false;
    }

    /**
     * Finds object in Window with id or returns nullptr.
     *
     * @returns pointer to the object if found else nullptr.
     */
    template<class Object, typename = std::enable_if<std::is_base_of<GUIObject, Object>::value>>
    Object *find(long id) {
        std::map<long, GUIObject *>::const_iterator it = objects.find(id);
        return it != objects.end() ? dynamic_cast<Object *>(it->second) : nullptr;
    }

    /**
     * Creates objects when window is created.
     */
    void createObjects();

    /**
     * Performs click on a button found by id. If not found, nothing happens.
     */
    void performClick(long id);

    /**
     * Shows confirm dialog box with the title and the message.
     *
     * @returns true if confirmed.
     */
    bool showConfirmDialog(const char *title, const char *message) const;

    /* Canvas */

    /**
     * Get reference to canvas.
     */
    Canvas &getCanvas();

    /**
     * Adds handler to canvas.
     */
    void addOnDrawHandler(OnDrawHandle &&);

    /**
     * Redraws the window.
     */
    void redraw();
};

#endif
