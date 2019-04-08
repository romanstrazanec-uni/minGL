#include <iostream>
#include "include.h"

using namespace std;
int main(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    Window window;
    window.setTitle("title");
    window.addHandler(MessageHandler(WM_PAINT, [](HWND h, UINT m, WPARAM w, LPARAM l){
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
        EndPaint(h, &ps);
    }));
    window.addHandler(MessageHandler(WM_CLOSE, [](HWND h, UINT m, WPARAM w, LPARAM l){
        if (MessageBox(h, "Really quit?", "My application", MB_OKCANCEL) == IDOK) DestroyWindow(h);
    }));
    if(!window.create()) return 1;
    return (int) (window.show(nCmdShow));
}
