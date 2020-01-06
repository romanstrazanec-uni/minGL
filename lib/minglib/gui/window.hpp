#ifndef MINGL_WINDOW_INCLUDED
#define MINGL_WINDOW_INCLUDED

#include "basewindow.hpp"
#include "button.hpp"
#include "edittext.hpp"
#include "label.hpp"

#include "../messaging/messagehandler.hpp"
#include "../graphics/canvas.hpp"

#include <map>

/** Derived main Window to create and show window. */
class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers{};
    std::map<long, GUIObject *> objects{};
    Canvas canvas;

    /**
     * Allows addition of GUIObjects passed as rvalue. Template class Object should be subclass of GUIObject.
     *
     * @tparam Object
     * @returns a pointer allocated for the passed object stored in the window
     */
    template<class Object>
    Object *addObject(Object &&);

public:
    /* Constructors */

    Window();

    explicit Window(const char *title);

    Window(UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    Window(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    ~Window() override;

    /* Message handling */

    LRESULT handleMessage(WindowMessage &&) override;

    /** Adds a message handler to respond to window messages. */
    void addHandler(MessageHandler &&);

    /** Adds a message handler to respond to specified message with handle function. */
    void addHandler(WindowMessage &&, Handle &&);

    void addOnMouseMoveHandler(std::function<void(Window *, POINT)> &&);

    /* Object manipulation */

    /**
     * Adds an created object to window.
     *
     * @param onlyAdd: default = false => firstly sets the parent of the object to this window.
     */
    void addObject(GUIObject *, bool onlyAdd = false);

    /* Label additions. */

    void addLabel(Label *);

    Label *addLabel(Label &&);

    Label *addLabel(long id, const char *text, int x, int y, int width, int height);

    /* EditText additions. */

    void addEditText(EditText *);

    EditText *addEditText(EditText &&);

    EditText *addEditText(long id, int x, int y, int width, int height);

    EditText *addEditText(long id, const char *text, int x, int y, int width, int height);

    /* Button additions. */

    void addButton(Button *);

    Button *addButton(Button &&);

    /**
     * Adds a button with specified title at certain position relative to the window.
     * Assign id to the button to respond with later assigned onClick method.
     *
     * @returns pointer to the newly created button.
     */
    Button *addButton(long id, const char *title, int x, int y, int width, int height);

    /**
     * Adds a button with specified title at certain position relative to the window.
     * Assign id to the button to respond with assigned onClick method.
     *
     * @returns pointer to the newly created button.
     */
    Button *addButton(long id, const char *title, int x, int y, int width, int height, void (*onClick)(Window *));

    /** Removes object from window. @returns true if found and removed. */
    template<class Object, typename = std::enable_if<std::is_base_of<GUIObject, Object>::value>>
    bool remove(Object *object) {
        // todo: map.erase(id)?
        for (std::map<long, GUIObject *>::const_iterator it = objects.begin(); it != objects.end(); it++)
            if (it->second == object) {
                objects.erase(it);
                object->setParent(nullptr, true);
                return true;
            }
        return false;
    }

    template<class Object>
    Object *find(long id) {
        std::map<long, GUIObject *>::const_iterator it = objects.find(id);
        return it != objects.end() ? dynamic_cast<Object *>(it->second) : nullptr;
    }

    /** Creates objects when window is created. */
    void createObjects();

    /** Performs click on a button found by id. If not found, nothing happens. */
    void performClick(long id);
};

#endif
