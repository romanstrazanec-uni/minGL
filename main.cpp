#include <iostream>
#include "include.h"

using namespace std;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    Window window;
    window.setTitle("title");
    if(!window.create()) return 1;
    return (int) (window.show(nCmdShow));
}
