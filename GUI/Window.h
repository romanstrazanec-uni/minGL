#ifndef LIBGRAPHICS_WINDOW_H
#define LIBGRAPHICS_WINDOW_H

#include <windows.h>

class Window {
private:
    WNDCLASSEX wc;
    HWND hwnd;
    int x, y, width, height;
    char *title;
    char CLASS_NAME[16];
    static UINT32 wndCount;

    void setClassName();

public:
    explicit Window(char *title);

    Window(int x, int y, int width, int height, char *title);
    virtual ~Window();

    bool create();
    WPARAM show(int nCmdShow);

    void initialize();
    void setWindowProcedure(LRESULT CALLBACK (*wndProc)(HWND, UINT, WPARAM, LPARAM));
    void setIcon(HINSTANCE, LPCSTR);
    void setSmallIcon(HINSTANCE, LPCSTR);
    void setCursor(HINSTANCE, LPCSTR);
    void setMenuName(LPCSTR);
    void setBackground(HBRUSH);
    void setStyle(UINT);
    void setWindowExtraBytes(int);
    void setClassExtraBytes(int);
};

#endif
