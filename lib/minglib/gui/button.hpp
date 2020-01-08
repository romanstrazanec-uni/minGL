#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include "guiobject.hpp"

#include <functional>

typedef std::function<void(Window *)> OnClickHandle;

class Button : public GUIObject {
    OnClickHandle onClick{};

public:
    Button() = default;
    Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Button(long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, OnClickHandle);
    Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height);
    Button(Window *window, long id, const char *title, UINT16 x, UINT16 y, UINT16 width, UINT16 height, OnClickHandle);

    void addOnClickListener(void (*)(Window *));

    void removeOnClickListener();

    void performClick();

    const char *getTitle() const;
};

#endif
