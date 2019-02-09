#ifndef WINDOWSGUI_WINDOW_H
#define WINDOWSGUI_WINDOW_H

#include <windows.h>

class Window {
private:
    WNDCLASSEX wc;
    HINSTANCE hInstance;
    HWND hwnd;
    int x, y, width, height;
    char *wndTitle;
    char wndClass[8];
    static BYTE wndCount;

private:
    int initialize();
    bool create();

public:
    Window(HINSTANCE hInstance, char *wndTitle);

    Window(HINSTANCE hInstance, int x, int y, int width, int height, char *wndTitle);

    virtual ~Window();
    WPARAM show(int nCmdShow);
};

#endif
