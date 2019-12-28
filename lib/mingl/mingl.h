#ifndef MINGL_INCLUDED
#define MINGL_INCLUDED

#define main() WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)

#include <windows.h>

#ifdef MINGL_DEBUG
#include <iostream>
#endif

#include <mingl/gui/window.hpp>

#endif
