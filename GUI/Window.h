#ifndef LIBGRAPHICS_WINDOW_H
#define LIBGRAPHICS_WINDOW_H

#include <windows.h>

class Window {
private:
    HWND hwnd;
    int x, y, width, height;
    char *title;
    char CLASS_NAME[16];
    static UINT32 wndCount;

public:
    explicit Window(char *title);

    Window(int x, int y, int width, int height, char *title);
    virtual ~Window();

    bool create(WNDCLASSEX &);
    WPARAM show(int nCmdShow);

    static WNDCLASSEX getDefaultClass();

    static void setWindowProcedure(WNDCLASSEX &, LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM));

    static void setIcon(WNDCLASSEX &, HINSTANCE, LPCSTR);

    static void setSmallIcon(WNDCLASSEX &, HINSTANCE, LPCSTR);

    static void setCursor(WNDCLASSEX &, HINSTANCE, LPCSTR);

    static void setMenuName(WNDCLASSEX &, LPCSTR);

    static void setBackground(WNDCLASSEX &, HBRUSH);

    static void setStyle(WNDCLASSEX &, UINT);

    static void setWindowExtraBytes(WNDCLASSEX &, int);

    static void setClassExtraBytes(WNDCLASSEX &, int);
};

#endif
