#ifndef WINDOWSGUI_WINDOW_H
#define WINDOWSGUI_WINDOW_H

#include <windows.h>

class Window {
private:
    WNDCLASSEX wc;
    HINSTANCE hInstance;
    HWND hwnd;
    int x{CW_USEDEFAULT}, y{CW_USEDEFAULT}, width{100}, height{100};
    char * windowTitle;
    const char szClassName[14] = "myWindowClass";

private:
    void initialize();
    void registerW();
    bool create();
public:
    Window(HINSTANCE hInstance, char * windowTitle);
    Window(HINSTANCE hInstance, unsigned int x, unsigned int y, unsigned int width, unsigned int height, char * windowTitle);
    WPARAM show(int nCmdShow);
};


#endif //WINDOWSGUI_WINDOW_H
