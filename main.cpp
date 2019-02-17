#include <iostream>
#include "include.h"

class MainWindow: public Window<MainWindow> {
public:
    LRESULT handleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override {
        switch (msg) {
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(getWindowHandle(), &ps);
                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
                EndPaint(getWindowHandle(), &ps);
            }
                return 0;
            case WM_CLOSE:
                if (MessageBox(getWindowHandle(), "Really quit?", "My application", MB_OKCANCEL) == IDOK)
                    DestroyWindow(getWindowHandle());
                return 0;
            default:
                return DefWindowProc(getWindowHandle(), msg, wparam, lparam);
        }
    }
};

using namespace std;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
    MainWindow window;
    window.setTitle("title");
    if(!window.create()) return 1;
    return (int) (window.show(nCmdShow));
}
