#ifndef MINGL_WINDOW_INCLUDED
#define MINGL_WINDOW_INCLUDED

#include "basewindow.hpp"
#include "button.hpp"
#include "numberinput.hpp"
#include "label.hpp"

#include "../messages/messagehandler.hpp"
#include "../graphics/canvas.hpp"

#include <map>

typedef std::function<void(Gdiplus::Point &&)> &&MouseHandle;

/** Derived main Window to create and show window. */
class Window : public BaseWindow<Window> {
    std::map<UINT, MessageHandler> messageHandlers{};
    std::map<long, GUIObject *> objects{};
    Canvas canvas;

    void addOnMouseEventHandler(WindowMessage &&wm, MouseHandle);

public:
    explicit Window(const char *title = "");
    Window(UINT16 x, UINT16 y);
    Window(UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Window(const char *title, UINT16 x, UINT16 y);
    Window(const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    ~Window() override;

    /* Message handling */

    LRESULT handleMessage(WindowMessage &&) override;

    /** Adds a message handler to respond to window messages. */
    void addHandler(MessageHandler &&);

    /** Adds a message handler to respond to specified message with handle function. */
    void addHandler(WindowMessage &&, Handle &&);

    void addOnMouseMoveHandler(MouseHandle);
    void addOnLeftMouseButtonDownHandler(MouseHandle);
    void addOnLeftMouseButtonUpHandler(MouseHandle);
    void addOnMiddleMouseButtonDownHandler(MouseHandle);
    void addOnMiddleMouseButtonUpHandler(MouseHandle);
    void addOnRightMouseButtonDownHandler(MouseHandle);
    void addOnRightMouseButtonUpHandler(MouseHandle);

    /* Object manipulation */

    /**
     * Allows addition of GUIObjects passed as rvalue. Template class Object should be subclass of GUIObject.
     *
     * @tparam Object
     * @returns a pointer allocated for the passed object stored in the window
     */
    template<class Object>
    Object *addObject(Object &&);

    /**
     * Adds an created object to window.
     *
     * @param onlyAdd: default = false => firstly sets the parent of the object to this window.
     */
    void addObject(GUIObject *, bool onlyAdd = false);

    /* Label additions. */

    void addLabel(Label *);
    Label *addLabel(Label &&);
    Label *addLabel(long id, const char *text, UINT16 x, UINT16 y);
    Label *addLabel(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* TextInput additions. */

    void addTextInput(TextInput *);
    TextInput *addTextInput(TextInput &&);
    TextInput *addTextInput(long id, UINT16 x, UINT16 y);
    TextInput *addTextInput(long id, const char *text, UINT16 x, UINT16 y);
    TextInput *addTextInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    TextInput *addTextInput(long id, const char *text, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* NumberInput additions. */

    void addNumberInput(NumberInput *);
    NumberInput *addNumberInput(NumberInput &&);
    NumberInput *addNumberInput(long id, UINT16 x, UINT16 y);
    NumberInput *addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y);
    NumberInput *addNumberInput(long id, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    NumberInput *addNumberInput(long id, UINT64 number, UINT16 x, UINT16 y, UINT16 width, UINT16 height);

    /* Button additions. */

    void addButton(Button *);
    Button *addButton(Button &&);
    Button *addButton(long id, const char *title, UINT16 x, UINT16 y, OnClickHandle && = nullptr);
    Button *
    addButton(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, OnClickHandle && = nullptr);

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

    void computeSize() override;

    /** Performs click on a button found by id. If not found, nothing happens. */
    void performClick(long id);

    bool showMessageDialog(const char *title, const char *message) const;

    /* Canvas */

    const Canvas &getCanvas() const;

    void addOnDrawHandler(std::function<void(Gdiplus::Graphics *)> &&);

    void redraw();
};

#endif
