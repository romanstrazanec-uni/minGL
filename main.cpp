#include "GUI/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex = Window::getDefaultClass();
    Window window((char *) "Title");
    if (!window.create(wcex)) return 1;
    return (int) (window.show(nCmdShow));
}
