#include <windows.h>
#include <d2d1.h>
#include "GUI/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    try {
        Window window(hInstance, 0, 0, 1024, 768, (char *) ("The title of my window"));
        return (int)(window.show(nCmdShow));
    } catch (EXCEPTION_REGISTRATION exception_registration) { return 0; }
}