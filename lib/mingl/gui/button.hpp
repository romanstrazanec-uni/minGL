#ifndef MINGL_BUTTON_INCLUDED
#define MINGL_BUTTON_INCLUDED

#include <functional>

#include <mingl/gui/guiobject.hpp>

class Button : public GUIObject {
    std::function<void()> onClick{nullptr};

public:
    Button() = default;

    Button(long id, const char *title, int x, int y, int width, int height);

    Button(long id, const char *title, int x, int y, int width, int height, std::function<void()> onClick);

    Button(Window *window, long id, const char *title, int x, int y, int width, int height);

    Button(Window *window, long id, const char *title, int x, int y, int width, int height,
           std::function<void()> onClick);

    void addOnClickListener(std::function<void()>);

    void removeOnClickListener();

    void performClick();

    const char *getTitle() const;
};

#endif
