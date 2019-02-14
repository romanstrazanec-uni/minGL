#include "GUI/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    Window window((char *) "Title");
    if (!window.create()) return 1;
    return (int) (window.show(nCmdShow));
}
