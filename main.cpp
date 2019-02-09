#define showwindow
#ifndef UNICODE
#define UNICODE
#endif

#ifdef showwindow
#include <windows.h>
#include "GUI/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    Window window(hInstance, (char *) ("The title of my window"));
    return (int) (window.show(nCmdShow));
}
#else
#include <iostream>
using namespace std;
int main(){
    return 0;
}
#endif