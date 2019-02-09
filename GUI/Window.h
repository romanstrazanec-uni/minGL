#ifndef LIBGRAPHICS_WINDOW_H
#define LIBGRAPHICS_WINDOW_H

#include <windows.h>

class Window {
private:
    WNDCLASSEX wc;
    HWND hwnd;
    int x, y, width, height;
    char *title;
    char wndClass[8];
    static BYTE wndCount;

public:
    Window(HINSTANCE hInstance, char *title);

    Window(HINSTANCE hInstance, int x, int y, int width, int height, char *title);
    virtual ~Window();

    bool create();
    WPARAM show(int nCmdShow);

    void setWindowProcedure(LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM));
};

#endif
