#define showwindow
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>

using namespace std;

#ifdef showwindow
#include <windows.h>
#include "GUI/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    Window window(hInstance, (char *) ("The title of my window"));
    if (!window.create()) return 2;
    return (int) (window.show(nCmdShow));
}
#else
int main(){
    return 0;
}
#endif